#include "UI.hpp"

//��`�̍��W���T�C�Y��ݒ�
void GetRectangleData(RectangleData& data, glm::vec2  pos, glm::vec2  size)
{
	data.pos = glm::vec2 (pos.x - size.x, pos.y - size.y);	//���W
	data.size = glm::vec2 (pos.x + size.x, pos.y + size.y);	//�T�C�Y
}
