#include "DxLib.h"

typedef struct {
    int x, y, img, muki, walking_flag;
}ch_t;

int hantei[15][20] = {
        { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
        { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
        { 1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
        { 1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
        { 1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
        { 1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
        { 1,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1 },
        { 1,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1 },
        { 1,1,1,1,1,0,0,0,0,0,1,0,0,0,1,0,0,0,1,1 },
        { 1,1,1,1,1,0,0,0,1,1,1,0,0,0,1,0,0,0,1,1 },
        { 1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1 },
        { 1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
        { 1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
        { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
        { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
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

    if (ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK || DxLib_Init() == -1) return -1; //ウィンドウ化と初期化処理

    ch.x = 320;
    ch.y = 160;
    ch.walking_flag = 0;
    ch.muki = 3;

    SetDrawScreen(DX_SCREEN_BACK);                                                 //描画先を裏画面に設定
    LoadDivGraph("char.png", 16, 4, 4, 32, 32, image);//画像を分割してimage配列に保存

    while (!ProcessMessage() && !ClearDrawScreen() && !GetHitKeyStateAll(Key) && !Key[KEY_INPUT_ESCAPE]) {
        //↑ﾒｯｾｰｼﾞ処理        ↑画面をｸﾘｱ         ↑ｷｰﾎﾞｰﾄﾞ入力状態取得       ↑ESCが押されると終了

            /*白い壁を描画*/
        for (i = 0; i < 15; i++)
            for (j = 0; j < 20; j++)
                if (hantei[i][j] == 1)
                    DrawBox(j * 32, i * 32, (j + 1) * 32, (i + 1) * 32, GetColor(255, 255, 255), TRUE);

        if (ch.x % 32 == 0 && ch.y % 32 == 0) {         //座標が32で割り切れたら入力可能
            ch.walking_flag = 1;         //歩くフラグを立てる。
            if (Key[KEY_INPUT_UP] == 1)  //上ボタンが押されたら
                ch.muki = 0;         //上向きフラグを立てる
            else if (Key[KEY_INPUT_LEFT] == 1)  //左ボタンが押されたら
                ch.muki = 1;         //左向きフラグを立てる
            else if (Key[KEY_INPUT_DOWN] == 1)  //下ボタンが押されたら
                ch.muki = 2;         //下向きフラグを立てる
            else if (Key[KEY_INPUT_RIGHT] == 1)  //右ボタンが押されたら
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

        ch.img = image[(ch.x % 32 + ch.y % 32) / 8 + ch.muki * 4];            //画像をセット

        DrawGraph(ch.x, ch.y, ch.img, TRUE);//画像を描画

        ScreenFlip();
    }

    DxLib_End();
    return 0;
}