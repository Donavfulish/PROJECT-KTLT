#include <iostream>
#include "struct.h"
#include "soundlib.h"
#include <string>
#include <fstream>
using namespace std;
void RegisterWindow();

bool IsMouseOverInputBox(InputBox& inputBox)
{
    return CheckCollisionPointRec(GetMousePosition(), inputBox.rect);
}

void DrawInputBox(InputBox& inputBox)
{
    char cursor = '\0';
    if (inputBox.active == true) cursor = '_';
    DrawRectangleRec(inputBox.rect, inputBox.active ? Fade(YELLOW, 0.3f) : Fade(WHITE, 0.6f));
    DrawRectangleLines(inputBox.rect.x, inputBox.rect.y, inputBox.rect.width, inputBox.rect.height, BLACK);
    DrawTextEx(inputBox.font, (inputBox.text + cursor).c_str(), { inputBox.rect.x + 10, inputBox.rect.y + inputBox.rect.height / 4 }, inputBox.rect.height * 0.7, 2, BLACK);
}

void DrawInputBox_Hide(InputBox& inputBox)
{
    char cursor = '\0';
    if (inputBox.active == true) cursor = '_';
    DrawRectangleRec(inputBox.rect, inputBox.active ? Fade(YELLOW, 0.3f) : Fade(WHITE, 0.6f));
    DrawRectangleLines(inputBox.rect.x, inputBox.rect.y, inputBox.rect.width, inputBox.rect.height, BLACK);
    string hide_password = "";
    for (char c : inputBox.text)
    {
        hide_password += "*";
    }
    DrawTextEx(inputBox.font, (hide_password + cursor).c_str(), { inputBox.rect.x + 10, inputBox.rect.y + inputBox.rect.height / 4 }, inputBox.rect.height * 0.7, 2, BLACK);
}

void setInputBoxActive(InputBox& inputBox)
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (IsMouseOverInputBox(inputBox)) {
            inputBox.active = true;
        }
        else {
            inputBox.active = false;
        }
    }
}

void fillTextInputBox(InputBox& inputBox)
{
    if (inputBox.active)
    {
        int keyPressed = GetKeyPressed();
        if (keyPressed != 0) {
            char inputChar;
            if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
                // Nếu Shift được nhấn, sử dụng mã ASCII trả về từ hàm GetKeyPressed()
                inputChar = (char)keyPressed;
            }
            else {
                // Nếu không, chuyển đổi ký tự từ in hoa sang in thường
                if (keyPressed >= KEY_A && keyPressed <= KEY_Z) {
                    inputChar = (char)(keyPressed + ('a' - 'A'));
                }
                else {
                    inputChar = (char)keyPressed;
                }
            }
            if (keyPressed >= KEY_KP_0 && keyPressed <= KEY_KP_9)
            {
                keyPressed -= KEY_KP_0 - KEY_ZERO;
                inputChar = (char)keyPressed;
            }
            if (keyPressed >= '0' && keyPressed <= '9' || (keyPressed >= 'A' && keyPressed <= 'Z') || (keyPressed >= 'a' && keyPressed <= 'z')) {
                if (MeasureTextEx(inputBox.font, (inputBox.text + inputChar).c_str(), inputBox.rect.height * 0.7, 2).x < inputBox.rect.width) {
                    inputBox.text += inputChar;
                }
            }
            else if (keyPressed == KEY_BACKSPACE) {
                if (!inputBox.text.empty()) {
                    inputBox.text.pop_back();
                }
            }
            else if (keyPressed == KEY_ESCAPE) {
                inputBox.text = "";
                inputBox.active = false;
            }
        }
    }
}

string codePassword(string password)
{
    string coded_password = "";
    for (int i = password.size() - 1; i >= 0; i--)
    {
        coded_password += password[i] + (219 - 'z');
    }
    return coded_password;
}

string decodePassword(string password)
{
    string decoded_password = "";
    for (int i = password.size() - 1; i >= 0; i--)
    {
        decoded_password += password[i] - (219 - 'z');
    }
    return decoded_password;
}

void readFileAccount(Account*& account, int& n) // n là số tài khoảng trong data (trong File)
{
    ifstream f;
    f.open("Data\\Account.txt");
    f >> n;
    f.ignore();
    account = new Account[n];
    for (int i = 0; i < n; i++)
    {
        string username, password;
        f >> username;
        f >> password;
        f.ignore();
        account[i].username = username;
        account[i].password = decodePassword(password);
    }
    f.close();
}


#define WRONG_PASS 1
#define UNAVAILABLE 2
#define VALID 3
int checkAccountStatus(Account account, Account* availableAccount, int n)
{
    // Kiểm tra tình trạng tài khoảng đã nhập trên data
    for (int i = 0; i < n; i++)
    {
        if (availableAccount[i].username == account.username)
        {
            if (availableAccount[i].password == account.password)
            {
                return VALID;
            }
            else
            {
                return WRONG_PASS;
            }
        }
    }
    return UNAVAILABLE;
}

#define BUTTON_LOGIN 1
#define BUTTON_REGISTER 2
// Hàm thực hiện chức năng khi nút Login/Register được bấm.
// Return False -> Tài khoản nhập không hợp lệ
// Return True -> Tài khoản nhập hợp lệ
bool Account_ButtonPressed(int button, Account account, Account* availableAccount, int n, string& message, bool status)
{
    // Kiểm tra xem nút có được bấm không, nếu có thì thưc hiện các câu lệnh dưới
    bool buttonActive = status;
    Rectangle rect = { 330, 305, 138, 43 };
    if (CheckCollisionPointRec(GetMousePosition(), rect))
    {
        DrawRectangleRec(rect, Fade(RED, 0.4f));
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            buttonActive = true;
        }
    }
    // Kiểm tra xem thông tin account nhập vào có đầy đủ hay chưa
    if (account.username == "" || account.password == "")
    {
        message = "Please fill your account's information.";
        return false;
    }
    else
    {
        if (message == "Please fill your account's information."
            || message == "Click LOGIN or Enter when you are done."
            || message == "Click REGISTER or Enter when you are done.")
            if (button == BUTTON_LOGIN) message = "Click LOGIN or Enter when you are done.";
            else if (button == BUTTON_REGISTER) message = "Click REGISTER or Enter when you are done.";
    }
    if (buttonActive == false) return false;

    // Nếu nút được bấm hoặc được kích hoạt khi press Enter thì thực hiện các câu lệnh ở dưới
    DrawRectangleRec(rect, Fade(RED, 0.4f));

    // Kiểm tra trạng thái tài khoản được nhập
    int accountStatus = checkAccountStatus(account, availableAccount, n);

    // Nếu nút Login được bấm
    if (button == BUTTON_LOGIN)
    {
        switch (accountStatus)
        {
        case UNAVAILABLE:
            PlaySound(sound_Wrong);
            message = "Unavailable username. Register?";
            break;
        case WRONG_PASS:
            PlaySound(sound_Wrong);
            message = "Wrong password. Please try again.";
            break;
        case VALID:
            PlaySound(sound_Correct);
            return true;
        }
        return false;
    }

    // Nếu nút Register được bấm
    else if (button == BUTTON_REGISTER)
    {
        switch (accountStatus)
        {
        case UNAVAILABLE:
            PlaySound(sound_Correct);
            message = "Register successfully! Please log in your new account.";
            return true;
        case WRONG_PASS:
            PlaySound(sound_Wrong);
            message = "The username has been used. Try another one.";
            break;
        case VALID:
            PlaySound(sound_Wrong);
            message = "The username has been used. Try another one.";
        }
        return false;
    }
}


#pragma region LOGIN FUNCTIONS
// Nếu bấm vào nút Register trên màn hình Login thì tới cửa sổ Register
void gotoRegister(Account& account, Account*& availableAccount, int& n)
{
    Rectangle rect = { 483.9, 394.3, 102.1, 26.7 };
    RegisterWindow();
    delete[] availableAccount;
    readFileAccount(availableAccount, n);
}

void refillButtonPressed(InputBox& inputBox_username, InputBox& inputBox_password)
{
    Rectangle rect_username = { 618.9, 192.3, 40, 40.3 };
    // Nếu nút refill Username được bấm
    if (CheckCollisionPointRec(GetMousePosition(), rect_username))
    {
        DrawRectangleRec(rect_username, Fade(BLACK, 0.4f));
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            inputBox_username.text = "";
            inputBox_username.active = true;
        }
    }

    Rectangle rect_password = { 618.9, 243.7, 40, 40.3 };
    // Nếu nút refill Username được bấm
    if (CheckCollisionPointRec(GetMousePosition(), rect_password))
    {
        DrawRectangleRec(rect_password, Fade(BLACK, 0.4f));
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            inputBox_password.text = "";
            inputBox_password.active = true;
        }
    }
}
bool clickonRegister()
{
    Rectangle rect = { 483.9, 394.3, 102.1, 26.7 };
    if (CheckCollisionPointRec(GetMousePosition(), rect))
    {
        DrawRectangleRec(rect, Fade(RED, 0.2f));
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            return true;
        }
    }
    return false;
}

void DrawMessage(Font font, string message)
{
    Vector2 textSize = MeasureTextEx(font, message.c_str(), 28, 1);
    if (message == "Register successfully! Please log in your new account.")
    {
        DrawTextEx(font, message.c_str(), { 400 - textSize.x / 2, 160 }, 28, 1, Fade(DARKGREEN, 0.8f));
    }
    else DrawTextEx(font, message.c_str(), { 400 - textSize.x / 2, 160 }, 28, 1, Fade(RED, 0.8f));
}

// Giao diện tạo cửa sổ đăng nhập: Pikachu - Login
void LoginWindow()
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Pikachu - Login");

    Font font = LoadFont("Roboto.ttf");
    Texture2D texture_Login = LoadTexture("Background_Login.png");
    InputBox inputBox_Username = { Rectangle { 319, 193, 300, 40 }, "", font, false };
    InputBox inputBox_Password = { Rectangle { 319, 244, 300, 40 }, "", font, false };

    SetTargetFPS(60);

    // Lấy dữ liệu những Account hiện có trong Data (trong File)
    int n;
    Account* availableAccount;
    readFileAccount(availableAccount, n);

    string message; // Biến lưu thông báo cho người dùng
    Account account; // Biến account nhập từ bàn phím

    while (!WindowShouldClose()) {
        DrawTexture(texture_Login, 0, 0, WHITE);
        // Username 
        setInputBoxActive(inputBox_Username);
        fillTextInputBox(inputBox_Username);
        account.username = inputBox_Username.text;
        // Password 
        setInputBoxActive(inputBox_Password);
        fillTextInputBox(inputBox_Password);
        account.password = inputBox_Password.text;

        // Thực hiện chuyển ô nhập khi Enter hoặc Tab
        bool loginSuccess = false; // Biến lưu kết quả login
        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_TAB))
        {
            if (inputBox_Username.active == true)
            {
                inputBox_Username.active = false;
                inputBox_Password.active = true;
            }
            else if (!IsKeyPressed(KEY_TAB) && inputBox_Password.active == true)
            {
                loginSuccess = Account_ButtonPressed(BUTTON_LOGIN, account, availableAccount, n, message, true);
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawInputBox(inputBox_Username);
        DrawMessage(font, message);
        if (loginSuccess == false) // Nếu khi nhập xong password người dùng không nhấn Enter/Tab thì check xem người dùng có click vào Login không
            loginSuccess = Account_ButtonPressed(BUTTON_LOGIN, account, availableAccount, n, message, false);
        refillButtonPressed(inputBox_Username, inputBox_Password);
        bool accessRegister = false;
        if (clickonRegister()) accessRegister = true;
        DrawInputBox_Hide(inputBox_Password);
        EndDrawing();

        // Nếu đăng nhập thành công
        if (loginSuccess == true)
        {
            User.username = account.username;
            User.password = account.password;
            GameStarting_Menu();
            break;
        }

        if (accessRegister == true)
        {
            PlaySound(sound_ClickOnButton);
            gotoRegister(account, availableAccount, n);
        }
    }
    delete[] availableAccount;
    UnloadTexture(texture_Login);
    UnloadFont(font);
    CloseWindow();
}

#pragma endregion

#pragma region REGISTER FUNCTIONS
void pushAccountToFile(Account account, Account*& availableAccount, int& n)
{
    fstream f;
    f.open("Data\\Account.txt");
    f << n + 1 << endl;
    f << endl;
    for (int i = 0; i < n; i++)
    {
        f << availableAccount[i].username << endl;
        f << codePassword(availableAccount[i].password) << endl;
        f << endl;
    }
    n++;
    f << account.username << endl;
    f << codePassword(account.password) << endl;
    f.close();

    delete[] availableAccount;
    // Cập nhật lại availableAccount
    readFileAccount(availableAccount, n);
}

bool clickonLogin()
{
    Rectangle rect = { 512.8, 394.3, 68.4, 26.7 };
    if (CheckCollisionPointRec(GetMousePosition(), rect))
    {
        DrawRectangleRec(rect, Fade(RED, 0.2f));
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            return true;
        }
    }
    return false;
}

void RegisterWindow()
{
    SetWindowTitle("Pikachu - Register");
    Font font = LoadFont("Roboto.ttf");
    Texture2D texture_Register = LoadTexture("Background_Register.png");
    InputBox inputBox_Username = { Rectangle { 319, 193, 300, 40 }, "", font, false };
    InputBox inputBox_Password = { Rectangle { 319, 244, 300, 40 }, "", font, false };

    SetTargetFPS(60);

    // Lấy dữ liệu những Account hiện có trong Data (trong File)
    int n;
    Account* availableAccount;
    readFileAccount(availableAccount, n);

    string message; // Biến lưu thông báo cho người dùng
    Account account; // Biến account nhập từ bàn phím

    // Biến kiểm tra xem dữ liệu tài khoản vừa đăng kí thành công đã được đẩy lên file chưa
    bool alreadyUpdate = false;
    bool registerSuccess = false; // Biến lưu kết quả register
    while (!WindowShouldClose()) {
        DrawTexture(texture_Register, 0, 0, WHITE);
        // Username 
        setInputBoxActive(inputBox_Username);
        fillTextInputBox(inputBox_Username);
        account.username = inputBox_Username.text;
        // Password 
        setInputBoxActive(inputBox_Password);
        fillTextInputBox(inputBox_Password);
        account.password = inputBox_Password.text;

        // Thực hiện chuyển ô nhập khi Enter hoặc Tab
        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_TAB))
        {
            if (inputBox_Username.active == true)
            {
                inputBox_Username.active = false;
                inputBox_Password.active = true;
            }
            else if (!IsKeyPressed(KEY_TAB) && inputBox_Password.active == true)
            {
                registerSuccess = Account_ButtonPressed(BUTTON_REGISTER, account, availableAccount, n, message, true);
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawInputBox(inputBox_Username);
        DrawMessage(font, message);
        if (registerSuccess == false) // Nếu sau khi nhập xong người dùng không nhấn Enter/Tab thì kiểm tra xem người dùng có click vào Register không
            registerSuccess = Account_ButtonPressed(BUTTON_REGISTER, account, availableAccount, n, message, false);
        refillButtonPressed(inputBox_Username, inputBox_Password);
        DrawInputBox(inputBox_Password);
        // Nếu bấm chữ Login thì đến cửa sổ Pikachu - Login
        bool accessLogin = false;
        if (clickonLogin()) accessLogin = true;

        // Nếu register thành công thì thay đổi dữ liệu trong File (thêm 1 account)
        if (alreadyUpdate == false && registerSuccess)
        {
            pushAccountToFile(account, availableAccount, n);
            alreadyUpdate = true;
            registerSuccess = false;
        }
        if (registerSuccess == false) alreadyUpdate = false;
        EndDrawing();

        if (accessLogin == true)
        {
            PlaySound(sound_ClickOnButton);
            SetWindowTitle("Pikachu - Login");
            break;
        }
    }
    delete[] availableAccount;
    UnloadTexture(texture_Register);
    UnloadFont(font);
    CloseWindow();
}
#pragma endregion