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

int IsAbleToGo(int x, int y, int muki) {//�i�߂邩�𔻒肷��
    if (muki == 0)//������Ȃ�
        if (hantei[y / 32 - 1][x / 32] == 1)//�i�߂邩����
            return 1;//�G���[
    if (muki == 1)//�������Ȃ�
        if (hantei[y / 32][x / 32 - 1] == 1)
            return 1;
    if (muki == 2)//�������Ȃ�
        if (hantei[y / 32 + 1][x / 32] == 1)
            return 1;
    if (muki == 3)//�E�����Ȃ�
        if (hantei[y / 32][x / 32 + 1] == 1)
            return 1;
    return 0;//����
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    int Sceen = 0;
    int image[16], i, j;
    char Key[256];
    ch_t ch;
    int Image[192];//192�̉摜���i�[����z��
    LoadDivGraph("�摜/TileA2.png", 192, 16, 12, 32, 32, Image);//�摜��16�ɕ�������Image�z��ɕۑ�

    if (ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK || DxLib_Init() == -1) return -1; //�E�B���h�E���Ə���������


    LoadDivGraph("�摜/�L�����N�^10.png", 16, 4, 4, 32, 32, image);//�摜�𕪊�����image�z��ɕۑ�
    int GameStart = LoadGraph("�摜/GameStart1.tiff");
    int GameClear2 = LoadGraph("�摜/StageClear.tiff");
    int Handle1 = LoadGraph("�摜/Q1.tiff"); // �摜�̃��[�h
    int Handle2 = LoadGraph("�摜/Q2.tiff");
    int Handle3 = LoadGraph("�摜/Q3.tiff");
    int Handle4 = LoadGraph("�摜/Q4.tiff");
    int cassiopeia1 = LoadGraph("�摜/�J�V�I�y�A��1.tiff");
    int cassiopeia2 = LoadGraph("�摜/�J�V�I�y�A��2.tiff");
    int cassiopeia3 = LoadGraph("�摜/�J�V�I�y�A��3.tiff");
    int cassiopeia4 = LoadGraph("�摜/�J�V�I�y�A��4.tiff");
    int cassiopeia5 = LoadGraph("�摜/�J�V�I�y�A��5.tiff");
    int Map = LoadGraph("�摜/�J�V�I�y�A��1.tiff");
    int Question1 = LoadGraph("�摜/���1.tiff");
    int Question2 = LoadGraph("�摜/���3.tiff");
    int Question3 = LoadGraph("�摜/���last.tiff");
    int Question4 = LoadGraph("�摜/Q3.tiff");
    int Question5 = LoadGraph("�摜/���last.tiff");
    int KeyHandle1 = LoadGraph("�摜/Key1.tiff"); // �摜�̃��[�h
    int KeyHandle2 = LoadGraph("�摜/Key2.tiff"); // �摜�̃��[�h
    int KeyHandle3 = LoadGraph("�摜/Key3.tiff"); // �摜�̃��[�h
    int KeyHandle4 = LoadGraph("�摜/Key4.tiff"); // �摜�̃��[�h
    int ItemHandle1 = LoadGraph("�摜/ItemKey1.tiff"); // �摜�̃��[�h
    int ItemHandle2 = LoadGraph("�摜/ItemKey2.tiff"); // �摜�̃��[�h
    int ItemHandle3 = LoadGraph("�摜/ItemKey3.tiff"); // �摜�̃��[�h
    int GameClear = LoadGraph("�摜/GameClear.tiff"); // �摜�̃��[�h
    ch.x = 288;
    ch.y = 416;
    ch.walking_flag = 0;
    ch.muki = 2;
    bool  keyhandle1 = false; //�A�C�e�����̕\��
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


    SetDrawScreen(DX_SCREEN_BACK);                                                 //�`���𗠉�ʂɐݒ�



 


    while (!ProcessMessage() && !ClearDrawScreen() && !GetHitKeyStateAll(Key) && !Key[KEY_INPUT_ESCAPE]) {
        //��ү���ޏ���        ����ʂ�ر         �����ް�ޓ��͏�Ԏ擾       ��ESC���������ƏI��
        Keyboard_Update();

        if (Sceen == 0){
            DrawGraph(0, 0, GameStart, true);
            DrawString(240, 80, "WhiteHouse", GetColor(255, 255, 255));
            DrawString(140, 120, "�������l���͐X�[���ɂ���قɋ����{�ʂœ����Ă��܂��B", GetColor(255, 255, 255));
            DrawString(140, 140, "����Ɠ����Ɍ��ւ̌����������Ă��܂�", GetColor(255, 255, 255));
            DrawString(140, 160, "�����߂��Ă��܂����B", GetColor(255, 255, 255));
            DrawString(140, 180, "���ׂẴJ�M���W�߂Ċق���E�o���悤�B", GetColor(255, 255, 255));
            DrawString(140, 220, "������@", GetColor(255, 255, 255));
            DrawString(140, 240, "�ړ���", GetColor(255, 255, 255));
            DrawString(140, 260, "W�őO�@�@�@S�Ō�", GetColor(255, 255, 255));
            DrawString(140, 280, "A�ō��@�@�@D�ŉE", GetColor(255, 255, 255));
            DrawString(140, 300, "Q�Ŗ���������A�A�C�e�����擾������", GetColor(255, 255, 255));
            DrawString(140, 320, "�}�b�v�����邱�Ƃ��ł��܂��B", GetColor(255, 255, 255));
            DrawString(140, 340, "�Q�[�����X�^�[�g������ŏ���Q��", GetColor(255, 255, 255));
            DrawString(140, 360, "�}�b�v�����邱�Ƃ��������߂��܂��B", GetColor(255, 255, 255));
            DrawString(140, 380, "����3��ނ��肷�ׂďW�߂�ƃQ�[����", GetColor(255, 255, 255));
            DrawString(140, 400, "�Q�[�����N���A���邱�Ƃ��ł��܂��B", GetColor(255, 255, 255));
            DrawString(140, 420, "G�L�[�ŃQ�[���X�^�[�g", GetColor(255, 255, 255));
            if (Key[KEY_INPUT_G] == 1) {//Map2
                Sceen = 1;
                }
        }
        if (ch.x == 288 && ch.y == 416 && Key[KEY_INPUT_RETURN] == 1 && keyhandle1 == true && keyhandle2 == true && keyhandle3 == true) {
            Sceen = 2;
        }
    if (Sceen == 2) {
        DrawGraph(0, 0, GameClear2, true);
        DrawString(140, 280, "��l���͖����A�ق���E�o�ł����B", GetColor(0, 0, 0));
        DrawString(140, 300, "�������A�O�͂��łɑ��z�������Ă���,���邩�����B", GetColor(0, 0, 0));
        DrawString(140, 320, "����قǒ������ԁA�قɂ�����l����", GetColor(0, 0, 0));
        DrawString(140, 340, "�}���ŉƂɋA�����̂�����...", GetColor(0, 0, 0));
        DrawString(140, 380, "�V��ł���Ă��肪�Ƃ�!!", GetColor(0, 0, 0));
        DrawString(140, 400, "ESC�L�[����������Q�[�����I���ł����B", GetColor(0, 0, 0));
    }
  

        if (Sceen == 1) {
            /*�����ǂ�`��*/
            for (i = 0; i < 15; i++)
                for (j = 0; j < 20; j++)
                    if (hantei[i][j] == 1)
                        DrawBox(j * 32, i * 32, (j + 1) * 32, (i + 1) * 32, GetColor(255, 255, 255), TRUE);

            if (ch.x % 32 == 0 && ch.y % 32 == 0) {         //���W��32�Ŋ���؂ꂽ����͉\
                if (!TextDisplay) {
                    ch.walking_flag = 1;         //�����t���O�𗧂Ă�B
                    if (Key[KEY_INPUT_W] == 1)  //��{�^���������ꂽ��
                        ch.muki = 0;         //������t���O�𗧂Ă�
                    else if (Key[KEY_INPUT_A] == 1)  //���{�^���������ꂽ��
                        ch.muki = 1;         //�������t���O�𗧂Ă�
                    else if (Key[KEY_INPUT_S] == 1)  //���{�^���������ꂽ��
                        ch.muki = 2;         //�������t���O�𗧂Ă�
                    else if (Key[KEY_INPUT_D] == 1)  //�E�{�^���������ꂽ��
                        ch.muki = 3;         //�E�����t���O�𗧂Ă�
                    else                                    //���̃{�^����������ĂȂ�������
                        ch.walking_flag = 0; //�����Ȃ��t���O�𗧂Ă�
                    if (ch.walking_flag == 1)    //���������Ȃ�
                        if (IsAbleToGo(ch.x, ch.y, ch.muki) == 1)//�s���悪�����Ȃ��Ȃ�
                            ch.walking_flag = 0;                  //�����Ȃ��t���O�𗧂Ă�B
                }
            }

            if (ch.walking_flag == 1 && TextDisplay == false) {        //�����t���O�������Ă�����
                if (ch.muki == 0)        //������Ȃ�ch.y���W�����炷
                    ch.y--;
                else if (ch.muki == 1)        //�������Ȃ�ch.x���W�����炷
                    ch.x--;
                else if (ch.muki == 2)        //�������Ȃ�ch.y���W�𑝂₷
                    ch.y++;
                else if (ch.muki == 3)        //�E�����Ȃ�ch.x���W�𑝂₷
                    ch.x++;
            }

            //�e�X�g�p
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
                MapDisplay = !MapDisplay;//���6�s�ō��͌����Ă���l��true�Ȃ�false�ɂ��āAfalse�Ȃ�true�ɂ���

            }

            if (MapDisplay)
                DrawGraph(0, 0, Map, true);

            if (Key[KEY_INPUT_Q] == 1) {//Map2
                if (ch.x == 96 && ch.y == 352 && ch.muki == 2) {
                    Map = LoadGraph("�摜/�J�V�I�y�A��2.tiff");
                }
            }
            if (Key[KEY_INPUT_Q] == 1) {//Map3
                if (ch.x == 64 && ch.y == 64 && ch.muki == 2) {
                    Map = LoadGraph("�摜/�J�V�I�y�A��3.tiff");
                }
            }
            if (Key[KEY_INPUT_Q] == 1) {//Map4
                if (ch.x == 512 && ch.y == 352 && ch.muki == 0) {
                    Map = LoadGraph("�摜/�J�V�I�y�A��4.tiff");
                }
            }
            if (Key[KEY_INPUT_Q] == 1) {//Map5
                if (ch.x == 288 && ch.y == 192 && ch.muki == 3) {
                    Map = LoadGraph("�摜/�J�V�I�y�A��5.tiff");
                }
            }

            //��蕶
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
                TextDisplay = !TextDisplay;//���6�s�ō��͌����Ă���l��true�Ȃ�false�ɂ��āAfalse�Ȃ�true�ɂ���
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


            //�q���g
            if (TextDisplay) {//��1
                if (ch.x == 288 && ch.y == 384 && ch.muki == 1) {
                    DrawGraph(0, 0, Question1, true);
                }
            }
            if (TextDisplay) {//��2
                if (ch.x == 288 && ch.y == 320 && ch.muki == 3) {
                    DrawGraph(0, 0, Question2, true);
                }
            }

            if (TextDisplay) {//��3
                if (ch.x == 288 && ch.y == 256 && ch.muki == 1) {
                    DrawGraph(0, 0, Handle2, true);
                }
            }
            if (TextDisplay) {//��4
                if (ch.x == 288 && ch.y == 192 && ch.muki == 3) {
                    DrawBox(150, 350, 450, 450, (255, 255, 255), true);
                    DrawFormatString(170, 370, (0, 0, 0), "�Ō�̒n�}��������!!", i);
                    DrawFormatString(170, 400, (0, 0, 0), "�n�}�ɕω���...", i);

                }
            }
            if (TextDisplay) {//��5
                if (ch.x == 288 && ch.y == 96 && ch.muki == 1) {
                    DrawGraph(0, 0, Question3, true);
                }
            }

            //�A�C�e��

            if (TextDisplay) {//item1
                if (ch.x == 96 && ch.y == 352 && ch.muki == 2) {
                    if (Keyboard_Get(KEY_INPUT_Q) == 1 && changetexthandle1 == 0) {
                        changetexthandle1 = 1;
                    }
                    else if (changetexthandle1 == 1) {
                        DrawGraph(50, 350, ItemHandle1, true);
                        DrawBox(150, 350, 450, 450, (255, 255, 255), true);
                        DrawFormatString(170, 355, (0, 0, 0), "�A�C�e������!!", i);
                        DrawFormatString(170, 390, (0, 0, 0), "����̕����̃q���g��������!", i);
                        DrawFormatString(170, 410, (0, 0, 0), "����A�n�}�ɕω���...", i);

                        keyhandle1 = true;
                        itemhandle1 = false;
                        //keyhandle0 = false;
                        if (Keyboard_Get(KEY_INPUT_Q) == 1) {
                            changetexthandle1 = 2;
                        }
            
                    }
                    else if (changetexthandle1 == 2) {
                            DrawBox(150, 350, 450, 450, (255, 255, 255), true);
                            DrawFormatString(170, 355, (0, 0, 0), "�����Ȃ��悤���B", i);
                        
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
                        DrawFormatString(170, 355, (0, 0, 0), "�A�C�e������!!", i);
                        DrawFormatString(170, 390, (0, 0, 0), "�E���̕����̃q���g��������!", i);
                        DrawFormatString(170, 420, (0, 0, 0), "����A�n�}�ɕω���...", i);

                        keyhandle2 = true;
                        itemhandle2 = false;

                        if (Keyboard_Get(KEY_INPUT_Q) == 1) {
                            changetexthandle2 = 2;
                        }
                    }
                    else if (changetexthandle2 == 2) {
                        DrawBox(150, 350, 450, 450, (255, 255, 255), true);
                        DrawFormatString(170, 355, (0, 0, 0), "�����Ȃ��悤���B", i);
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
                    DrawFormatString(170, 355, (0, 0, 0), "�A�C�e������!!", i);
                    DrawFormatString(170, 390, (0, 0, 0), "�E��̕����̃q���g��������!", i);
                    DrawFormatString(170, 420, (0, 0, 0), "����A�n�}�ɕω���...", i);

                    keyhandle3 = true;
                    itemhandle3 = false;
                    if (Keyboard_Get(KEY_INPUT_Q) == 1) {
                        changetexthandle3 = 2;
                }
            }
                    else if (changetexthandle3 == 2) {
                          DrawBox(150, 350, 450, 450, (255, 255, 255), true);
                          DrawFormatString(170, 355, (0, 0, 0), "�����Ȃ��悤���B", i);
                      }
                }
            }
         

            if (keyhandle1 == 1) {
                DrawGraph(125, 5, KeyHandle1, true);//�A�C�e����1
            }
            if (keyhandle2 == 1) {
                DrawGraph(185, 5, KeyHandle2, true);//�A�C�e����2
            }
            if (keyhandle3 == 1) {
                DrawGraph(245, 5, KeyHandle3, true);//�A�C�e����3
            }
            if (keyhandle1 == true&& keyhandle2 == true&& keyhandle3 == true) {
                DrawGraph(305, 5, KeyHandle4, true);//�A�C�e����4
            }
            ch.img = image[(ch.x % 32 + ch.y % 32) / 8 + ch.muki * 4];            //�摜���Z�b�g
   

            for (int i = 0; i < 9; i++) {
                if (i++) {
                    DrawBox(30 + i * 30, 0, 90 + i * 30, 60, GetColor(0, 0, 0), false);
                }

            }
            if (!TextDisplay) {
                DrawGraph(ch.x, ch.y, ch.img, TRUE);//�摜��`��
            }
            DrawRotaGraph(400, 200, 1.0, 0, Image[64], TRUE); //�摜�̕`��
            DrawRotaGraph(400, 300, 1.0, 0, Image[98], TRUE); //�摜�̕`��

        }
       
            ScreenFlip();
         }

         DxLib_End();
         return 0;
     }

