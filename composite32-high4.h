// �R���|�W�b�g�J���[�M���o�̓v���O���� ���𑜓x��4�i������f�j�@PIC32MX150F128B�p�w�b�_�[�t�@�C���@by K.Tanaka
//�@4�r�b�g�P��VRAM�A16�F

#define X_RES	256 // �������𑜓x
#define Y_RES	224 // �c�����𑜓x
#define H_WORD	(X_RES/4) // 1�s����̃��[�h��(16bit�P��)

// ���̓{�^���̃|�[�g�A�r�b�g��`
#define KEYPORT PORTB
#define KEYUP 0x0400
#define KEYDOWN 0x0080
#define KEYLEFT 0x0100
#define KEYRIGHT 0x0200
#define KEYSTART 0x0800
#define KEYFIRE 0x4000

extern volatile char drawing;		//�@�\�����Ԓ���-1
extern volatile unsigned short drawcount;		//�@1��ʕ\���I�����Ƃ�1�����B�A�v������0�ɂ���B
							// �Œ�1��͉�ʕ\���������Ƃ̃`�F�b�N�ƁA�A�v���̏���������ʊ��ԕK�v���̊m�F�ɗ��p�B

extern unsigned short VRAM[];
extern void start_composite(void); //�J���[�R���|�W�b�g�o�͊J�n
extern void stop_composite(void); //�J���[�R���|�W�b�g�o�͒�~
extern void init_composite(void); //�J���[�R���|�W�b�g�o�͏�����
extern void clearscreen(void); //��ʃN���A
extern void set_palette(unsigned char n,unsigned char b,unsigned char r,unsigned char g); //�J���[�p���b�g�ݒ�
