#include "DxLib.h"

typedef struct {
    int x, y, img, muki, walking_flag;
}ch_t;

int hantei[15][21] = {
        { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
        { 1,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,1 },
        { 1,0,1,0,1,0,1,1,1,0,1,0,0,0,0,0,0,0,0,1,1 },
        { 1,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,1 },
        { 1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
        { 1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,1 },
        { 1,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,1 },
        { 1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1 },
        { 1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,1 },
        { 1,0,1,1,1,1,0,0,1,0,1,0,0,0,0,0,0,0,0,1,1 },
        { 1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,1 },
        { 1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
        { 1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,1 },
        { 1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,1 },
        { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
};

int IsAbleToGo(int x, int y, int muki) {//進めるかを判定する
    if (muki == 0)//上向きなら
        if (hantei[y / 32 - 1][x / 32] == 1)//進めるか判定
            return 1;//エラー
    if (muki == 1)//左向きなら
        if (hantei[y / 32][x / 32 - 1] == 1)
            return 1;
    if (muki == 2)//下向きなら
        if (hantei[y / 32 + 1][x / 32] == 1)
            return 1;
    if (muki == 3)//右向きなら
        if (hantei[y / 32][x / 32 + 1] == 1)
            return 1;
    return 0;//正常
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    int image[16], i, j;
    char Key[256];
    ch_t ch;
    int Image[192];//192個の画像を格納する配列
    LoadDivGraph("画像/TileA2.png", 192, 16, 12, 32, 32, Image);//画像を16個に分割してImage配列に保存

    if (ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK || DxLib_Init() == -1) return -1; //ウィンドウ化と初期化処理

    int Handle = LoadGraph("画像/キャラクタ01.png"); // 画像のロード
    ch.x = 288;
    ch.y = 416;
    ch.walking_flag = 0;
    ch.muki = 2;

    
    SetDrawScreen(DX_SCREEN_BACK);                                                 //描画先を裏画面に設定
    LoadDivGraph("画像/キャラクタ10.png", 16, 4, 4, 32, 32, image);//画像を分割してimage配列に保存


    while (!ProcessMessage() && !ClearDrawScreen() && !GetHitKeyStateAll(Key) && !Key[KEY_INPUT_ESCAPE]) {
        //↑ﾒｯｾｰｼﾞ処理        ↑画面をｸﾘｱ         ↑ｷｰﾎﾞｰﾄﾞ入力状態取得       ↑ESCが押されると終了

            /*白い壁を描画*/
        for (i = 0; i < 15; i++)
            for (j = 0; j < 20; j++)
                if (hantei[i][j] == 1)
                    DrawBox(j * 32, i * 32, (j + 1) * 32, (i + 1) * 32, GetColor(255, 255, 255), TRUE);

        if (ch.x % 32 == 0 && ch.y % 32 == 0) {         //座標が32で割り切れたら入力可能
            ch.walking_flag = 1;         //歩くフラグを立てる。
            if (Key[KEY_INPUT_W] == 1)  //上ボタンが押されたら
                ch.muki = 0;         //上向きフラグを立てる
            else if (Key[KEY_INPUT_A] == 1)  //左ボタンが押されたら
                ch.muki = 1;         //左向きフラグを立てる
            else if (Key[KEY_INPUT_S] == 1)  //下ボタンが押されたら
                ch.muki = 2;         //下向きフラグを立てる
            else if (Key[KEY_INPUT_D] == 1)  //右ボタンが押されたら
                ch.muki = 3;         //右向きフラグを立てる
            else                                    //何のボタンも押されてなかったら
                ch.walking_flag = 0; //歩かないフラグを立てる
            if (ch.walking_flag == 1)    //もし歩くなら
                if (IsAbleToGo(ch.x, ch.y, ch.muki) == 1)//行き先が歩けないなら
                    ch.walking_flag = 0;                  //歩かないフラグを立てる。
        }

        if (ch.walking_flag == 1) {        //歩くフラグが立っていたら
            if (ch.muki == 0)        //上向きならch.y座標を減らす
                ch.y--;
            else if (ch.muki == 1)        //左向きならch.x座標を減らす
                ch.x--;
            else if (ch.muki == 2)        //下向きならch.y座標を増やす
                ch.y++;
            else if (ch.muki == 3)        //右向きならch.x座標を増やす
                ch.x++;
        }
        if (Key[KEY_INPUT_Q] == 1) {//Q1
            if (ch.x == 32 && ch.y == 256 && ch.muki == 0) {
                DrawGraph(0, 0, Handle, true);
            }
        }
        if (Key[KEY_INPUT_Q] == 1) {//A1
            if (ch.x == 96 && ch.y == 384 && ch.muki == 0) {
                DrawGraph(0, 0, Handle, true);
            }
        }
        if (Key[KEY_INPUT_Q] == 1) {//Q3
            if (ch.x == 64 && ch.y == 32 && ch.muki == 2) {
                DrawGraph(0, 0, Handle, true);
            }
        }
        if (Key[KEY_INPUT_Q] == 1) {//Q3
            if (ch.x == 352 && ch.y == 288 &&ch.muki == 1) {
                DrawGraph(0, 0, Handle, true);
            }
        }
        if (Key[KEY_INPUT_Q] == 1) {//Q3
            if (ch.x == 352 && ch.y == 416 && ch.muki == 1) {
                DrawGraph(0, 0, Handle, true);
            }
        }
        if (Key[KEY_INPUT_Q] == 1) {//Q3
            if (ch.x == 512 && ch.y == 320 &&ch.muki == 0) {
                DrawGraph(0, 0, Handle, true);
            }
   
        }
        ch.img = image[(ch.x % 32 + ch.y % 32) / 8 + ch.muki * 4];            //画像をセット
        DrawFormatString(0, 0,(255, 255, 255), " % d",ch.x);
        DrawFormatString(0, 20, (255, 255, 255), " % d", ch.y);
        DrawGraph(ch.x, ch.y, ch.img, TRUE);//画像を描画
        DrawRotaGraph(400, 200, 1.0, 0, Image[64], TRUE); //画像の描画
        DrawRotaGraph(400, 300, 1.0, 0, Image[98], TRUE); //画像の描画
        //DrawGraph(0, 0, Handle, true);
        /*for (int m = 0; m < 15; m++) {//マップチップ
            for (int n = 0; n < 21; n++) {*/
            /* if (hantei[MapY][MapX] == 0) {
            DrawRotaGraph(32 + 16, 32 + 16, 1.0, 0, Image[64], TRUE); //画像の描画
        }
        else if (hantei[MapY][MapX] == 1) {
            DrawRotaGraph(16 + 32, 16 + 32, 1.0, 0, Image[98], TRUE); //画像の描画
        }*/
            //}
        //}*/
        ScreenFlip();
    }

    DxLib_End();
    return 0;
}