# JJUGGUMI 게임 과제1
팀 이름 : 퀀텀


조장:이재혁(20XXXX01)
팀원:이현상(20XXXX08),허지원(20XXXX88)


canvas.c : 무궁화 게임의 출력을 담당하는 코드입니다. 맵 출력, 버퍼, 플레이어 상태 창, 메시지 창 등을 출력하는데 필요한 소스코드 입니다.

jjuggumi.c : 처음 게임 시작 시 플레이어 수를 입력받고, 각각의 함수들을 불러와 게임을 실행시키는 메인함수입니다.

keyin.c : 0번 플레이어(직접 조종시키는 플레이어)의 입력을 받아주는 소스코드입니다.

mugunghwa.c : 랜덤하게 동작하는 플레이이어의 움직임과 맵의 버퍼, "무궁화 꽃이 피었습니다"문구 출력, 술래, 상태창 변화 등 게임에 필요한 기능들을 구현해 놓은 소스코드 입니다.


keyin.h : 0번 플레이어(직접 조종시키는 플레이어)를 조작할 키와 그 키에 맞는 값을 저장해 놓은 헤더파일입니다.

canvas.h : 맵과 상태창을 띄울 캔버스의 크기와, 버퍼, 맵의 관련된 함수를 저장해놓은 헤더파일입니다.

jjuggumi.h : 다른 소스코드의 공통으로 필요한 전역변수의 값을 저장해 놓은 소스코드입니다.
