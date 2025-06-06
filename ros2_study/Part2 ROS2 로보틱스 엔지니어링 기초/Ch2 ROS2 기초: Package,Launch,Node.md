## Ch02-01 Package, Node, Launch 개요 
---

 ### 1) 패키지(Package)란? 

<div align="left">
  <img src="https://github.com/user-attachments/assets/81d9b784-2405-487a-bd67-af846fcfe20a" height="350" width="700">
</div>

 ### 2) Python과 C++ Package 차이

<div align="left">
  <img src="https://github.com/user-attachments/assets/3e178417-1e11-40c4-b54b-56dd59d81aba" height="350" width="700">
</div>

 - Package.xml 파일은 해당 패키지를 누가 만들고 관리하는지와 패키지 빌드를 위해서 필요한 의존성 패키지에는 

   어떠한 것들이 있는지를 명시해 놓았다.

 - Python 패키지를 만들면 생성된 패키지 안에 동일한 패키지 이름의 디렉토리가 만들어져있다.

   그 안에는 해당 패키지와 관련된 python 소스코드가 존재한다.

 ### 3) 노드(Node) 란?

<div align="left">
  <img src="https://github.com/user-attachments/assets/e4897d53-82e9-4701-a260-cc39445f0345" height="350" width="700">
</div>

 ### 4) Launch 파일이란?
 
<div align="left">
  <img src="https://github.com/user-attachments/assets/a3778d42-c62b-477a-9764-c8656962e3a6" height="350" width="700">
</div>

 - Launch 파일은 실행 할 때 몇번 포트에서 매개변수를 가져올지를 정할 수 있다. 
 - ROS2 에서는 대부분 Python 파일로 launch 파일을 만든다.
