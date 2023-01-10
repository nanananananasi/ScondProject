#include "DxLib.h"

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

    int image[16], i, j;
    char Key[256];
    ch_t ch;
    int Image[192];//192�̉摜���i�[����z��
    LoadDivGraph("�摜/TileA2.png", 192, 16, 12, 32, 32, Image);//�摜��16�ɕ�������Image�z��ɕۑ�

    if (ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK || DxLib_Init() == -1) return -1; //�E�B���h�E���Ə���������

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
    ch.x = 288;
    ch.y = 416;
    ch.walking_flag = 0;
    ch.muki = 2;
    bool  keyhandle1 = false;
    bool  keyhandle2 = false;
    bool  keyhandle3 = false;

    SetDrawScreen(DX_SCREEN_BACK);                                                 //�`���𗠉�ʂɐݒ�
    LoadDivGraph("�摜/�L�����N�^10.png", 16, 4, 4, 32, 32, image);//�摜�𕪊�����image�z��ɕۑ�


    while (!ProcessMessage() && !ClearDrawScreen() && !GetHitKeyStateAll(Key) && !Key[KEY_INPUT_ESCAPE]) {
        //��ү���ޏ���        ����ʂ�ر         �����ް�ޓ��͏�Ԏ擾       ��ESC���������ƏI��

    

            /*�����ǂ�`��*/
            for (i = 0; i < 15; i++)
                 for (j = 0; j < 20; j++)
                     if (hantei[i][j] == 1)
                         DrawBox(j * 32, i * 32, (j + 1) * 32, (i + 1) * 32, GetColor(255, 255, 255), TRUE);

             if (ch.x % 32 == 0 && ch.y % 32 == 0) {         //���W��32�Ŋ���؂ꂽ����͉\
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

             if (ch.walking_flag == 1) {        //�����t���O�������Ă�����
                 if (ch.muki == 0)        //������Ȃ�ch.y���W�����炷
                     ch.y--;
                 else if (ch.muki == 1)        //�������Ȃ�ch.x���W�����炷
                     ch.x--;
                 else if (ch.muki == 2)        //�������Ȃ�ch.y���W�𑝂₷
                     ch.y++;
                 else if (ch.muki == 3)        //�E�����Ȃ�ch.x���W�𑝂₷
                     ch.x++;
             }
             if (Key[KEY_INPUT_Q] == 1) {//MAP
                     DrawGraph(0, 0, Map, true);
                 }


             if (Key[KEY_INPUT_Q] == 1) {//Q1
                 if (ch.x == 32 && ch.y == 288 && ch.muki == 0) {
                     DrawGraph(0, 0, Handle1, true);
                 }
             }
         
             if (Key[KEY_INPUT_Q] == 1) {//Q3
                 if (ch.x == 352 && ch.y ==320 && ch.muki == 1) {
                     DrawGraph(0, 0, Handle3, true);
                 }
             }
             if (Key[KEY_INPUT_Q] == 1) {//Q4
                 if (ch.x == 352 && ch.y == 416 && ch.muki == 1) {
                     DrawGraph(0, 0, Handle4, true);
                 }
             }
             if (Key[KEY_INPUT_Q] == 1) {//i1
                 if (ch.x == 96 && ch.y == 352 && ch.muki == 2) {
                     DrawGraph(0, 0, Handle1, true);
                     Map = LoadGraph("�摜/�J�V�I�y�A��2.tiff");
                     keyhandle1 = true;
                 }
             }
             if (Key[KEY_INPUT_Q] == 1) {//i2
                 if (ch.x == 64 && ch.y == 64 && ch.muki == 2) {
                     DrawGraph(0, 0, Handle2, true);
                     Map = LoadGraph("�摜/�J�V�I�y�A��3.tiff");
                     keyhandle2 = true;
                 }
             }
             if (Key[KEY_INPUT_Q] == 1) {//i4
                 if (ch.x == 512 && ch.y == 352 && ch.muki == 0) {
                     DrawGraph(0, 0, Handle1, true);
                     Map = LoadGraph("�摜/�J�V�I�y�A��4.tiff");
                     keyhandle3 = true;
                 }

             }
             if (Key[KEY_INPUT_Q] == 1) {//��1
                 if (ch.x == 288 && ch.y == 384 && ch.muki == 1) {
                     DrawGraph(0, 0, Question1, true);
                 }
             }
             if (Key[KEY_INPUT_Q] == 1) {//��2
                 if (ch.x == 288 && ch.y == 320 && ch.muki == 3) {
                     DrawGraph(0, 0, Question2, true);
                 }
             }
        
             if (Key[KEY_INPUT_Q] == 1) {//��3
                 if (ch.x == 288 && ch.y == 256 && ch.muki == 1) {
                     DrawGraph(0, 0, Handle2, true);
                 }
             }
             if (Key[KEY_INPUT_Q] == 1) {//��4
                 if (ch.x == 288 && ch.y == 192 && ch.muki == 3) {
                     Map = LoadGraph("�摜/�J�V�I�y�A��5.tiff");
                 }
             }
             if (Key[KEY_INPUT_Q] == 1) {//��5
                 if (ch.x == 288 && ch.y == 96 && ch.muki == 1) {
                     DrawGraph(0, 0, Question3, true);
                 }
             }
             ch.img = image[(ch.x % 32 + ch.y % 32) / 8 + ch.muki * 4];            //�摜���Z�b�g
             DrawFormatString(0, 0, (255, 255, 255), " % d", ch.x);
             DrawFormatString(0, 20, (255, 255, 255), " % d", ch.y);
             for (int i = 0; i < 15; i++) {
                 if (i++){
                     DrawBox(30 + i*30, 0, 90 + i*30, 60, GetColor(0, 0, 0), false);
                 }
               
             }
             if (keyhandle1 == 1) {
                 DrawGraph(125, 5, KeyHandle1, true);//�A�C�e����1
             }
             if (keyhandle2 == 1) {
                 DrawGraph(185, 5, KeyHandle2, true);//�A�C�e����1
             }
             if (keyhandle3 == 1) {
                 DrawGraph(245, 5, KeyHandle3, true);//�A�C�e����1
             }
             DrawGraph(ch.x, ch.y, ch.img, TRUE);//�摜��`��
             DrawRotaGraph(400, 200, 1.0, 0, Image[64], TRUE); //�摜�̕`��
             DrawRotaGraph(400, 300, 1.0, 0, Image[98], TRUE); //�摜�̕`��
             //DrawGraph(125, 5, KeyHandle1, true);//�A�C�e����1
             //DrawGraph(185, 5, KeyHandle2, true);//�A�C�e����2
             //DrawGraph(245, 5, KeyHandle3, true);//�A�C�e����3
            
             //DrawGraph(0, 0, Handle, true);
             /*for (int m = 0; m < 15; m++) {//�}�b�v�`�b�v
                 for (int n = 0; n < 21; n++) {*/
                 /* if (hantei[MapY][MapX] == 0) {
                 DrawRotaGraph(32 + 16, 32 + 16, 1.0, 0, Image[64], TRUE); //�摜�̕`��
             }
             else if (hantei[MapY][MapX] == 1) {
                 DrawRotaGraph(16 + 32, 16 + 32, 1.0, 0, Image[98], TRUE); //�摜�̕`��
             }*/
             //}
         //}*/
            ScreenFlip();
         }

         DxLib_End();
         return 0;
     }

