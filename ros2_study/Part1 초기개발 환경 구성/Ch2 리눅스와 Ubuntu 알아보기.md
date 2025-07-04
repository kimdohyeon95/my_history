## Ch02-01. Linux 이해하기 
---
 ### 1)  Linux 사용 예시
    
- 스마트폰과 태블릿: 안드로이드 운영체제는 리눅스 커널을 기반으로 하고, 스마트폰 운영체제 중의 하나이다. 
- 개인용 컴퓨터: 리눅스 배포판인 우분투,페도라 등도 서버 데스크톱 환경에서 사용될 수 있다. 
- 서버: 웹서버 ,이메일 서버,파일 서버등 많은 서버가 리눅스를 이용하여 운용된다.
 
   ex) aws, 구글 클라우드 플랫폼
- 임베디드 시스템: 가정용 기기등에서 소형 디바이스등에 리눅스라는 os가 들어가 있고, 네트워크 장비
  
  라우터나 스위치 등에도 들어가 있다.
- 엔터테인먼트: 스마트 TV나 DVR 등이 리눅스 기반으로 되어있고 게임 콘솔 개발자들도 리눅스 환경에서

  개발을하고 테스트를 진행한다.
- 로보틱스: ROS2 기반의 자율주행 로봇을 다루는 기업들 대부분은 리눅스 환경에서 개발을 한다. 


 ### 2) 리눅스 배포판

 - 리눅스 배포판은 우분투 외에도 많이 있지만 우분투가 최적화가 가장 잘 되어있고, 간결하고 쉽게 사용할 수 있다.
 - 높은 인지도와 많은 커뮤니티가 활성화 되어있어 문제가 생길 시, 빠른 해결이 가능하다. 
 - 우분투 gui 가 GNOME 라고하는 인터페이스를 가지고 있어 사용자 친화적인 UI를 가지고 있다. 

  ### 3) 리눅스의 구조 

<div align="left">
  <img src="https://github.com/user-attachments/assets/4bd8def8-42b0-4a30-9575-fd5e05baa055" height="300" width="450">
</div>
<br>

- Applications에서 명령어를 내리게되면 Shell이라는 아이가 해석을 하게되고 해석된 명령어를 Kernel에 전달하면

  Kernel이 Hardware를 제어하는 코드를 통해 Applications과 소통을 하면서 시스템의 모든 자원을 통제하게 된다.

   ### 4) 패키지 관리자 -apt
   
  - Advanced Packaging Tool의 약자
  - 데비안 리눅스 또는 파생된 배포판(우분투)에서 소프트웨어를 설치,제거,업데이트 할 때 사용함. 
  - sudo apt 의 의미는 root라고 하는 최고 관리자 권한으로 이러한 명령을 실행하겠다는 의미이다.

   ### 5) 리눅스 파일 시스템
<div align="left">
  <img src="https://github.com/user-attachments/assets/a7aa693d-2c6f-4ad6-8937-50ce0b940e3d" height="300" width="450">
</div>
<br>

  - 파일이라는 것은 주기억장치나 디스크 처럼 하드웨어 저장 공간에 저장되는 파일의 집합이다.
  - 파일 시스템이라는 것은 저장장치 내에서 데이터를 읽고 쓰기 위한 약속이다.
  - 리눅스에서는 최상단 root 아래 계층적으로 파일과 디렉토리가 존재한다.
  - root 라고 하는 것은 슬래쉬'/'로 표현하며 모든데이터의 시작점이며 일반적인 데이터를 제외한 중요한 데이터를 저장한다.
  - /bin 폴더는 리눅스의 기본명령어가 들어있는 디렉토리이다.
  - /boot 폴더는 부팅에 핵심적인 커널 이미지와 부팅 이미지를 파일로 담고 있는 디렉토리이다.
  - /etc 폴더는 lilo.config 파일이 존재하는데 그 안에 커널 부팅 이미지 파일이 들어있으면 부팅 시 중요한 역할을 한다.
  - /dev 폴더는 장치 파일들이 저장되어있는 디렉토리이다 . ex) 키보드 , 마우스 등
  - /home 폴더는 사용자들의 홈 디렉토리이고 들어가면 사용자 계정과 동일한 디렉토리가 생성된다.
  - /mnt 폴더는 파일시스템을 임시로 연결하는 디렉토리이다. 클라우드 서버와 임시로 연결할 때 사용된다.
  - 최상단 root 아래 /root 폴더가 있는데 시스템 관리자의 홈디렉토리이다.
  - /sbin 리눅스 커널과 관련된 정보가 들어있는 디렉토리이다.
  - /tmp 폴더는 temporary의 약자로 시스템 사용중에 발생한 임시 데이터가 저장되는 곳으로 부팅시 초기화가 된다.
  - /usr 폴더는 기본 실행파일과 라이브러리 파일 헤더 파일 응용프로그램이 파일 형태로 저장되어있는 디렉토리이다.
  - /var 시스템 운영 중에 발생한 데이터와 로그가 저장되는 디렉토리이다.
  - /opt 기본 소프트웨어를 제외하고 따로 추가한 소프트웨어가 저장되어있는 디렉토리이다. 

## Ch02-02. Linux 필수 명령어
---

 ### Linux 필수 명령어

 - #### Linux 명령어의 옵션
   
   `-`: 축약형 옵션 ex) -V 

   `--`: 풀네임 옵션 ex) --version

   `--help`: 명령어의 간단한 메뉴얼 호출

  #### ls
  - 현재 디렉토리의 파일 목록을 출력하는 명령어
  - `ls-l`: 현재 디렉토리의 파일을 자세히 보여준다.
  - `ls-a`: 현재 디렉토리에 있는 파일 + 숨긴파일(.파일명) 다 보여준다.
  - `ls-al`: -a와 -l 합친 옵션 

  #### pwd 
  - 현재 위치하고 있는 디렉토리를 알려주는 명령어

  #### mkdir 
  - 새로운 디렉토리를 생성해주는 명령어
  - ex) `mkdir new_directory_name`
  - `-p`: 필요하면 부모 디렉토리를 생성한다. `(--parents)`

  #### touch
  - 유효한 빈 파일을 작성하기 위한 명령어
  - 예시: `touch newfile.txt`

  #### cd 
  - 다른 디렉토리로 이동하기 위한 명령어
  - 예시: `cd /home/user`(user 디렉토리로 이동)
  - `상대경로`: 현재 디렉토리의 위치를 기준으로 다른 디렉토리의 위치를 표현하는 것

    `..`:  부모 디렉토리

      `cd..`: 현재 디렉토리의 부모 디렉토리로 이동하는 명령어

    `.`: 현재 디렉토리
  - `절대경로`: 최상위 디렉토리를 기준으로 경로를 표현하는 것

    `최상위 디렉토리`: 루트(root) 디렉토리라고 하고 `/`이다.
     `cd /`는 최상위 디렉토리로 이동한다는 의미

  #### rm 
  - 파일을 삭제하기 위한 명령어
  - `rm-rf 디렉토리명`: 파일이나 디렉토리가 담긴 디렉토리를 삭제

  #### cp 
  - 시스템에서 파일이나 디렉토리를 한 쪽에서 다른 쪽으로 복사하는 명령어
  - 예시: `cp source.txt destination.txt`(sourtxt.txt를 destination.txt로 복사)

  #### mv
  - 기존 위치에 있는 파일을 없애고, 지정한 다른 위치에 파일을 옮기는 명령어
  - ex) `mv mv.txt dir1/mv.txt
  - 파일명 바꾸고 싶을 때도 `mv` 사용

    ex) `mv rename.txt rename2.txt 
