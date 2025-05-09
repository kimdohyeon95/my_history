- ###  1. new & delete 연산자 
<br> 

<div align="left">
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="https://github.com/user-attachments/assets/2238d549-1009-4192-a39d-b3708278f580" height="200" width="350" >
</div>

<div align="left">
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="https://github.com/user-attachments/assets/1420d122-cacd-40f9-beb8-3a224cea5c0a" height="200" width="350" >
</div>

>> ✅ **C언어에서의 malloc과 free를 대신하는 키워드는 new와 delete이다.**

>> ✅ 키워드 new의 오른쪽 편에 할당할 대상의 자료형과 크기를 지정하는 것을 알 수 있다.

>> ✅ delete연산은 new 연산시 반환된 주소값을 대상으로 진행하고 할당된 영역이 배열의 구조일 경우 []를 추가로 명시해 주면 된다.
<br>

- ### 2. 힙 메모리에 할당된 변수의 접근
<br>
<div align="left">
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="https://github.com/user-attachments/assets/bc0959da-f7f1-4735-9636-b04b7f517c87" height="200" width="350" >
</div>

>> 위의 예제는 new 연산자를 사용하여 메모리 공간에 할당된 변수를 참조자로 접근하는 것을 나타낸다.

>> ✅ C++에서는 new 연산자를 이용하여 할당된 메모리 공간도 변수로 간주하여 참조자의 선언이 가능하도록 한다.   
