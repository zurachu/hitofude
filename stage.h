#ifndef H_HITOFUDE_STAGE_
#define H_HITOFUDE_STAGE_

#include <piece.h>

/// ���g���C����
BOOL IsRetry();

/// �I������
BOOL IsEnd();

/// �摜�̏�����
void InitImage();

/// �X�e�[�W������
void InitStage( char* data );

/// �X�e�[�W��ԍX�V
void UpdateStage();

/// �X�e�[�W�`��
void DrawStage();

#endif //  H_HITOFUDE_STAGE_

