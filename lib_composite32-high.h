// �R���|�W�b�g�J���[�M���o�̓v���O����
//�@PIC32MX150F128B�p�O���t�B�b�N���C�u�����p�w�b�_�[�t�@�C��

void pset(int x,int y,unsigned int c);
// (x,y)�̈ʒu�ɃJ���[c�œ_��`��

void putbmpmn(int x,int y,char m,char n,const unsigned char bmp[]);
// ��m*�cn�h�b�g�̃L�����N�^�[�����Wx,y�ɕ\��
// unsigned char bmp[m*n]�z��ɁA�P���ɃJ���[�ԍ�����ׂ�
// �J���[�ԍ���0�̕����͓����F�Ƃ��Ĉ���

void clrbmpmn(int x,int y,char m,char n);
// �cm*��n�h�b�g�̃L�����N�^�[����
// �J���[0�œh��Ԃ�

void line(int x1,int y1,int x2,int y2,unsigned int c);
// (x1,y1)-(x2,y2)�ɃJ���[c�Ő�����`��

void hline(int x1,int x2,int y,unsigned int c);
// (x1,y)-(x2,y)�ւ̐������C���������`��

void circle(int x0,int y0,unsigned int r,unsigned int c);
// (x0,y0)�𒆐S�ɁA���ar�A�J���[c�̉~��`��

void boxfill(int x1,int y1,int x2,int y2,unsigned int c);
// (x1,y1),(x2,y2)��Ίp���Ƃ���J���[c�œh��ꂽ�����`��`��

void circlefill(int x0,int y0,unsigned int r,unsigned int c);
// (x0,y0)�𒆐S�ɁA���ar�A�J���[c�œh��ꂽ�~��`��

void putfont(int x,int y,unsigned int c,int bc,unsigned char n);
//8*8�h�b�g�̃A���t�@�x�b�g�t�H���g�\��
//���W�ix,y)�A�J���[�ԍ�c
//bc:�o�b�N�O�����h�J���[�A�����̏ꍇ����
//n:�����ԍ�

void printstr(int x,int y,unsigned int c,int bc,unsigned char *s);
//���W(x,y)����J���[�ԍ�c�ŕ�����s��\���Abc:�o�b�N�O�����h�J���[

void printnum(int x,int y,unsigned char c,int bc,unsigned int n);
//���W(x,y)�ɃJ���[�ԍ�c�Ő��ln��\���Abc:�o�b�N�O�����h�J���[

void printnum2(int x,int y,unsigned char c,int bc,unsigned int n,unsigned char e);
//���W(x,y)�ɃJ���[�ԍ�c�Ő��ln��\���Abc:�o�b�N�O�����h�J���[�Ae���ŕ\��
