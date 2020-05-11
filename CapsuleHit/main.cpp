#include<DxLib.h>
#include<cmath>
#include"Geometry.h"


using namespace std;

///�J�v�Z���`��̕`��
void DrawCapsule(const Capsule& cap,unsigned int color) {
	DrawCircle(cap.posA.x, cap.posA.y, cap.radius, color);
	DrawCircle(cap.posB.x, cap.posB.y, cap.radius, color);

	auto v = cap.posB - cap.posA;
	auto angle = atan2(v.y, v.x)-DX_PI_F/2.0f;
	auto w = cos(angle)*cap.radius ;
	auto h = sin(angle)*cap.radius ;

	DrawQuadrangle(
		cap.posA.x - w, cap.posA.y - h,
		cap.posB.x - w, cap.posB.y - h,
		cap.posB.x + w, cap.posB.y + h,
		cap.posA.x + w, cap.posA.y + h, color, true);
}

///�Ƃ���_�𒆐S�ɉ�]���āA���̉�]��̍��W��Ԃ��܂��B
///@param center ��]���S�_
///@param angle ��]�p�x
///@param pos ���̍��W
///@return �ϊ���̍��W
Matrix RotatePosition(const Position2& center, float angle) {
	//�@���S�����_�ɕ��s�ړ�����
	//�A���_���S�ɉ�]����
	//�B���S�����̍��W�֖߂�

	Matrix mat = MultipleMat(TranslateMat(center.x, center.y),
		MultipleMat(RotateMat(angle),
			TranslateMat(-center.x, -center.y)));
	return mat;
	//��������������āA����̓_�𒆐S�ɉ�]���s���悤�ɂ��Ă��������B
}

Capsule RotateCapsule(Position2 center, float angle, const Capsule &cap) {
	Capsule ret = cap;

	




	return ret;
}

//�J�v�Z���Ɖ~�������������H
bool IsHit(const Capsule& cap, const Circle& cc) {



	//First ,We need to  Get The Second Vector2 
	Vector2 T = cc.pos -  cap.posA;
	Vector2 L = cap.posB - cap.posA;


	float len =(T * L) /( L * L);


	float shadowlen = Dot(T,L)/ L.Magnitude() ;

	//Find The Position Of The Vector

//	Position2 vertPos = (L.Normalized()* shadowlen) + cap.posA;

	//This is mainly To make a  ClampFloat
	float k = (Dot(T, L) / Dot(L, L));
	k =min(1,max(k,0));
//	k = min(0, max(k, 1));


	Position2 vertPos = cap.posA + (L*k);
	float d = (cc.pos - vertPos).Magnitude();
	return d <= cc.radius + cap.radius;	
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(true);

	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);
	Circle c(50, Position2(50, 50));
	Capsule cap(20,Position2(100,200),Position2(300,200));
	char keystate[256];
	float angle = 0.0f;



	Circle circle(50, Position2(50, 50));



	while (ProcessMessage() == 0) {
		ClearDrawScreen();

		int mx, my;
		GetMousePoint(&mx, &my);
		int minput = GetMouseInput();

		//�J�v�Z����]
		if (minput&MOUSE_INPUT_LEFT) {
			angle = 0.1f;
		}
		else if (minput&MOUSE_INPUT_RIGHT) {
			angle = -0.1f;
		}
		else {
			angle = 0.0f;
		}
		GetHitKeyStateAll(keystate);
		//�~������
		if (keystate[KEY_INPUT_RIGHT]) {
			c.pos.x = min(640, c.pos.x + 5);
		}
		else if (keystate[KEY_INPUT_LEFT]) {
			c.pos.x = max(0, c.pos.x -5);
		}
		if (keystate[KEY_INPUT_UP]) {
			c.pos.y = max(0, c.pos.y - 5);
		}
		else if (keystate[KEY_INPUT_DOWN]) {
			c.pos.y = min(480, c.pos.y + 5);
		}


		//�J�v�Z���`���RotatePosition�̌��ʂ̍s��ŉ�]�����Ă�������
		cap=RotateCapsule(Position2(mx, my), angle, cap);

		auto color = 0xffffff;
		if (IsHit(cap, c)) {
			color = 0xffaaaa;
		}


		DrawCircle(circle.pos.x, circle.pos.y, circle.radius, 0xff0000);



		DrawCircle(c.pos.x, c.pos.y, c.radius, color);
		DrawCapsule(cap, color);

		ScreenFlip();
	}

	DxLib_End();


}