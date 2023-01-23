#include "DxLib.h"
#include "Keyboard.h"

typedef struct {
    int x, y, img, muki, walking_flag;
}ch_t;

int hantei[15][21] = {
        { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
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
        { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
        { 1,0,0,1,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,1 },
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

    int Sceen = 0;
    int image[16], i, j;
    char Key[256];
    ch_t ch;
    int Image[192];//192個の画像を格納する配列
    LoadDivGraph("画像/TileA2.png", 192, 16, 12, 32, 32, Image);//画像を16個に分割してImage配列に保存

    if (ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK || DxLib_Init() == -1) return -1; //ウィンドウ化と初期化処理


    LoadDivGraph("画像/キャラクタ10.png", 16, 4, 4, 32, 32, image);//画像を分割してimage配列に保存
    int Handle1 = LoadGraph("画像/Q1.tiff"); // 画像のロード
    int Handle2 = LoadGraph("画像/Q2.tiff");
    int Handle3 = LoadGraph("画像/Q3.tiff");
    int Handle4 = LoadGraph("画像/Q4.tiff");
    int cassiopeia1 = LoadGraph("画像/カシオペア座1.tiff");
    int cassiopeia2 = LoadGraph("画像/カシオペア座2.tiff");
    int cassiopeia3 = LoadGraph("画像/カシオペア座3.tiff");
    int cassiopeia4 = LoadGraph("画像/カシオペア座4.tiff");
    int cassiopeia5 = LoadGraph("画像/カシオペア座5.tiff");
    int Map = LoadGraph("画像/カシオペア座1.tiff");
    int Question1 = LoadGraph("画像/問題1.tiff");
    int Question2 = LoadGraph("画像/問題3.tiff");
    int Question3 = LoadGraph("画像/問題last.tiff");
    int Question4 = LoadGraph("画像/Q3.tiff");
    int Question5 = LoadGraph("画像/問題last.tiff");
    int KeyHandle1 = LoadGraph("画像/Key1.tiff"); // 画像のロード
    int KeyHandle2 = LoadGraph("画像/Key2.tiff"); // 画像のロード
    int KeyHandle3 = LoadGraph("画像/Key3.tiff"); // 画像のロード
    int KeyHandle4 = LoadGraph("画像/Key4.tiff"); // 画像のロード
    int ItemHandle1 = LoadGraph("画像/ItemKey1.tiff"); // 画像のロード
    int ItemHandle2 = LoadGraph("画像/ItemKey2.tiff"); // 画像のロード
    int ItemHandle3 = LoadGraph("画像/ItemKey3.tiff"); // 画像のロード
    int GameClear = LoadGraph("画像/GameClear.tiff"); // 画像のロード
    ch.x = 288;
    ch.y = 416;
    ch.walking_flag = 0;
    ch.muki = 2;
    bool  keyhandle1 = false; //アイテム欄の表示
    bool  keyhandle2 = false;
    bool  keyhandle3 = false;
    bool itemhandle1 = true;
    bool itemhandle2 = true;
    bool itemhandle3 = true;
    int  changetexthandle1  = 0;
    int  changetexthandle2 = 0;
    int  changetexthandle3 = 0;

    bool TextDisplay = false;
    bool MapDisplay = false;


    SetDrawScreen(DX_SCREEN_BACK);                                                 //描画先を裏画面に設定



 


    while (!ProcessMessage() && !ClearDrawScreen() && !GetHitKeyStateAll(Key) && !Key[KEY_INPUT_ESCAPE]) {
        //↑ﾒｯｾｰｼﾞ処理        ↑画面をｸﾘｱ         ↑ｷｰﾎﾞｰﾄﾞ入力状態取得       ↑ESCが押されると終了
        Keyboard_Update();

        if (Sceen == 0){
            DrawString(240, 100, "WhiteHouse", GetColor(255, 255, 255));
            DrawString(140, 200, "操作方法", GetColor(255, 255, 255));
            DrawString(140, 220, "移動は", GetColor(255, 255, 255));
            DrawString(140, 240, "Wで前　　　Sで後", GetColor(255, 255, 255));
            DrawString(140, 260, "Aで左　　　Dで右", GetColor(255, 255, 255));
            DrawString(140, 280, "Qで問題を見たり、アイテムを取得したり", GetColor(255, 255, 255));
            DrawString(140, 300, "マップを見ることができます。", GetColor(255, 255, 255));
            DrawString(140, 320, "ゲームがスタートしたら最初にQで", GetColor(255, 255, 255));
            DrawString(140, 340, "マップを見ることをおすすめするよ", GetColor(255, 255, 255));
            DrawString(140, 360, "Gキーでゲームスタート", GetColor(255, 255, 255));
            if (Key[KEY_INPUT_G] == 1) {//Map2
                Sceen = 1;
                }
        }
        if (ch.x == 576 && ch.y == 224 && Key[KEY_INPUT_RETURN] == 1) {
            Sceen = 2;
        }
    if (Sceen == 2) {
        DrawString(140, 220, "遊んでくれてありがとう!!", GetColor(255, 255, 255));
        DrawString(140, 240, "ESCキーを押したらゲームを終了できるよ", GetColor(255, 255, 255));
    }

        if (Sceen == 1) {
            /*白い壁を描画*/
            for (i = 0; i < 15; i++)
                for (j = 0; j < 20; j++)
                    if (hantei[i][j] == 1)
                        DrawBox(j * 32, i * 32, (j + 1) * 32, (i + 1) * 32, GetColor(255, 255, 255), TRUE);

            if (ch.x % 32 == 0 && ch.y % 32 == 0) {         //座標が32で割り切れたら入力可能
                if (!TextDisplay) {
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
            }

            if (ch.walking_flag == 1 && TextDisplay == false) {        //歩くフラグが立っていたら
                if (ch.muki == 0)        //上向きならch.y座標を減らす
                    ch.y--;
                else if (ch.muki == 1)        //左向きならch.x座標を減らす
                    ch.x--;
                else if (ch.muki == 2)        //下向きならch.y座標を増やす
                    ch.y++;
                else if (ch.muki == 3)        //右向きならch.x座標を増やす
                    ch.x++;
            }

            //テスト用
            if (MapDisplay) {
                DrawString(5, 10, "MapDisplay == true", GetColor(0, 0, 0));
            }

            if (Keyboard_Get(KEY_INPUT_Q) == 1) {
                /* if (MapDisplay) {
                     MapDisplay = false;
                 }
                 else {
                     MapDisplay = true;
                 }*/
                MapDisplay = !MapDisplay;//上の6行で今は言っている値がtrueならfalseにして、falseならtrueにする

            }

            if (MapDisplay)
                DrawGraph(0, 0, Map, true);

            if (Key[KEY_INPUT_Q] == 1) {//Map2
                if (ch.x == 96 && ch.y == 352 && ch.muki == 2) {
                    Map = LoadGraph("画像/カシオペア座2.tiff");
                }
            }
            if (Key[KEY_INPUT_Q] == 1) {//Map3
                if (ch.x == 64 && ch.y == 64 && ch.muki == 2) {
                    Map = LoadGraph("画像/カシオペア座3.tiff");
                }
            }
            if (Key[KEY_INPUT_Q] == 1) {//Map4
                if (ch.x == 512 && ch.y == 352 && ch.muki == 0) {
                    Map = LoadGraph("画像/カシオペア座4.tiff");
                }
            }
            if (Key[KEY_INPUT_Q] == 1) {//Map5
                if (ch.x == 288 && ch.y == 192 && ch.muki == 3) {
                    Map = LoadGraph("画像/カシオペア座5.tiff");
                }
            }

            //問題文
            if (TextDisplay) {
                DrawString(5, 15, "TextDisplay == true", GetColor(0, 0, 0));
            }
            if (Keyboard_Get(KEY_INPUT_Q) == 1) {
                /* if (MapDisplay) {
                     MapDisplay = false;
                }
                else {
                     MapDisplay = true;
                }*/
                TextDisplay = !TextDisplay;//上の6行で今は言っている値がtrueならfalseにして、falseならtrueにする
            }

            if (TextDisplay) {//Quest1
                if (ch.x == 32 && ch.y == 288 && ch.muki == 0) {
                    DrawGraph(0, 0, Handle1, true);
                }
            }

            if (TextDisplay) {//Quest3
                if (ch.x == 352 && ch.y == 288 && ch.muki == 1) {
                    DrawGraph(0, 0, Handle3, true);
                }
            }
            if (TextDisplay) {//Quest4
                if (ch.x == 352 && ch.y == 416 && ch.muki == 1) {
                    DrawGraph(0, 0, Handle4, true);
                }
            }
            if (TextDisplay) {//Quest4
                if (ch.x == 448 && ch.y == 64 && ch.muki == 0) {
                    DrawGraph(0, 0, GameClear, true);
                }
            }


            //ヒント
            if (TextDisplay) {//☆1
                if (ch.x == 288 && ch.y == 384 && ch.muki == 1) {
                    DrawGraph(0, 0, Question1, true);
                }
            }
            if (TextDisplay) {//☆2
                if (ch.x == 288 && ch.y == 320 && ch.muki == 3) {
                    DrawGraph(0, 0, Question2, true);
                }
            }

            if (TextDisplay) {//☆3
                if (ch.x == 288 && ch.y == 256 && ch.muki == 1) {
                    DrawGraph(0, 0, Handle2, true);
                }
            }
            if (TextDisplay) {//☆4
                if (ch.x == 288 && ch.y == 192 && ch.muki == 3) {
                    DrawBox(150, 350, 450, 450, (255, 255, 255), true);
                    DrawFormatString(170, 370, (0, 0, 0), "最後の地図を見つけた!!", i);
                    DrawFormatString(170, 400, (0, 0, 0), "地図に変化が...", i);

                }
            }
            if (TextDisplay) {//☆5
                if (ch.x == 288 && ch.y == 96 && ch.muki == 1) {
                    DrawGraph(0, 0, Question3, true);
                }
            }

            //アイテム

            if (TextDisplay) {//item1
                if (ch.x == 96 && ch.y == 352 && ch.muki == 2) {
                    if (Keyboard_Get(KEY_INPUT_Q) == 1 && changetexthandle1 == 0) {
                        changetexthandle1 = 1;
                    }
                    else if (changetexthandle1 == 1) {
                        DrawGraph(50, 350, ItemHandle1, true);
                        DrawBox(150, 350, 450, 450, (255, 255, 255), true);
                        DrawFormatString(170, 355, (0, 0, 0), "アイテム入手!!", i);
                        DrawFormatString(170, 390, (0, 0, 0), "左上の部屋のヒントを見つけた!", i);
                        DrawFormatString(170, 410, (0, 0, 0), "おや、地図に変化が...", i);

                        keyhandle1 = true;
                        itemhandle1 = false;
                        //keyhandle0 = false;
                        if (Keyboard_Get(KEY_INPUT_Q) == 1) {
                            changetexthandle1 = 2;
                        }
            
                    }
                    else if (changetexthandle1 == 2) {
                            DrawBox(150, 350, 450, 450, (255, 255, 255), true);
                            DrawFormatString(170, 355, (0, 0, 0), "何もないようだ", i);
                        
                    }
                     
                }
                
            }

            if (TextDisplay) {//item2
                if (ch.x == 64 && ch.y == 64 && ch.muki == 2) {
                    if (Keyboard_Get(KEY_INPUT_Q) == 1 && changetexthandle2 == 0) {
                        changetexthandle2 = 1;
                    }
                    else if (changetexthandle2 == 1) {
                        DrawGraph(50, 350, ItemHandle2, true);
                        DrawBox(150, 350, 450, 450, (255, 255, 255), true);
                        DrawFormatString(170, 355, (0, 0, 0), "アイテム入手!!", i);
                        DrawFormatString(170, 390, (0, 0, 0), "右下の部屋のヒントを見つけた!", i);
                        DrawFormatString(170, 420, (0, 0, 0), "おや、地図に変化が...", i);

                        keyhandle2 = true;
                        itemhandle2 = false;

                        if (Keyboard_Get(KEY_INPUT_Q) == 1) {
                            changetexthandle2 = 2;
                        }
                    }
                    else if (changetexthandle2 == 2) {
                        DrawBox(150, 350, 450, 450, (255, 255, 255), true);
                        DrawFormatString(170, 355, (0, 0, 0), "何もないようだ", i);
                    }
                }
            }
            if (TextDisplay) {//item4
                if (ch.x == 512 && ch.y == 352 && ch.muki == 0) {
                      if (Keyboard_Get(KEY_INPUT_Q) == 1 && changetexthandle3 == 0) {
                        changetexthandle3 = 1;
                    }
                    else if (changetexthandle3 == 1) {
                    DrawGraph(50, 350, ItemHandle3, true);
                    DrawBox(150, 350, 450, 450, (255, 255, 255), true);
                    DrawFormatString(170, 355, (0, 0, 0), "アイテム入手!!", i);
                    DrawFormatString(170, 390, (0, 0, 0), "右上の部屋のヒントを見つけた!", i);
                    DrawFormatString(170, 420, (0, 0, 0), "おや、地図に変化が...", i);

                    keyhandle3 = true;
                    itemhandle3 = false;
                    if (Keyboard_Get(KEY_INPUT_Q) == 1) {
                        changetexthandle3 = 2;
                }
            }
                    else if (changetexthandle3 == 2) {
                          DrawBox(150, 350, 450, 450, (255, 255, 255), true);
                          DrawFormatString(170, 355, (0, 0, 0), "何もないようだ", i);
                      }
                }
            }
         

            if (keyhandle1 == 1) {
                DrawGraph(125, 5, KeyHandle1, true);//アイテム鍵1
            }
            if (keyhandle2 == 1) {
                DrawGraph(185, 5, KeyHandle2, true);//アイテム鍵2
            }
            if (keyhandle3 == 1) {
                DrawGraph(245, 5, KeyHandle3, true);//アイテム鍵3
            }
            if (keyhandle1 == true&& keyhandle2 == true&& keyhandle3 == true) {
                DrawGraph(305, 5, KeyHandle4, true);//アイテム鍵4
            }
            ch.img = image[(ch.x % 32 + ch.y % 32) / 8 + ch.muki * 4];            //画像をセット
            DrawFormatString(0, 0, (255, 255, 255), " % d", ch.x);
            DrawFormatString(0, 20, (255, 255, 255), " % d", ch.y);
            for (int i = 0; i < 9; i++) {
                if (i++) {
                    DrawBox(30 + i * 30, 0, 90 + i * 30, 60, GetColor(0, 0, 0), false);
                }

            }
            if (!TextDisplay) {
                DrawGraph(ch.x, ch.y, ch.img, TRUE);//画像を描画
            }
            DrawRotaGraph(400, 200, 1.0, 0, Image[64], TRUE); //画像の描画
            DrawRotaGraph(400, 300, 1.0, 0, Image[98], TRUE); //画像の描画

        }

             //DrawGraph(125, 5, KeyHandle1, true);//アイテム鍵1
             //DrawGraph(185, 5, KeyHandle2, true);//アイテム鍵2
             //DrawGraph(245, 5, KeyHandle3, true);//アイテム鍵3
            
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

