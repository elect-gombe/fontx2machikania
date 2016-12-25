#define WIDTH_X	30 // ������������
#define WIDTH_Y	27 // �c����������
#define ATTROFFSET	(WIDTH_X*WIDTH_Y) // VRAM��̃J���[�p���b�g�i�[�ʒu

extern volatile char drawing;		//�@�\�����Ԓ���-1
extern volatile unsigned short drawcount;		//�@1��ʕ\���I�����Ƃ�1�����B�A�v������0�ɂ���B
							// �Œ�1��͉�ʕ\���������Ƃ̃`�F�b�N�ƁA�A�v���̏���������ʊ��ԕK�v���̊m�F�ɗ��p�B
extern unsigned char TVRAM[]; //�e�L�X�g�r�f�I������
extern void start_composite(void); //�J���[�R���|�W�b�g�o�͊J�n
extern void stop_composite(void); //�J���[�R���|�W�b�g�o�͒�~
extern void init_composite(void); //�J���[�R���|�W�b�g�o�͏�����
extern void clearscreen(void); //��ʃN���A
extern void set_palette(unsigned char n,unsigned char b,unsigned char r,unsigned char g); //�p���b�g�ݒ�
extern void set_bgcolor(unsigned char b,unsigned char r,unsigned char g); //�o�b�N�O�����h�J���[�ݒ�

extern const unsigned char FontData[]; //�t�H���g�p�^�[����`
