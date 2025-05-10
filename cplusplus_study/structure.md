- ### C++에서 Structure의 정의 
 <br>
 
   #### &nbsp;&nbsp;&nbsp;&nbsp; 1) 구조체 내부에 함수를 정의한 경우
<div align="left">
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="https://github.com/user-attachments/assets/9c8d3c29-c19e-4b50-91e3-1bd1d01b495b" height="600" width="450" >
</div>

<div align="left">
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="https://github.com/user-attachments/assets/409c6353-34a2-433c-b71c-67b2a709fda1" height="250" width="450" >
</div>

<br>

   #### &nbsp;&nbsp;&nbsp;&nbsp; 2) 구조체 내부에 함수 선언을 하고 외부에 함수를 정의한 경우
<div align="left">
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="https://github.com/user-attachments/assets/8fe3fb29-a655-4ed4-9a2b-e90afffe638b" height="250" width="450" >
</div>

<div align="left">
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="https://github.com/user-attachments/assets/7d2d2d56-93a1-4048-99bd-6cfa41aa2437" height="500" width="450" >
</div>

>> ✅ **C++에서 구조체 변수를 선언할 때에는 C언어와 다르게 `struct` 키워드를 제외하고 선언할 수 있다.**

>> ✅ **또한 C++에서는 구조체 내부에 함수를 정의 할 수 있어서 함수를 종속적 관계로 표현할 수 있다.**

>> ✅ 2번 예시 처럼 구조체 내에 정의해야 할 함수가 많을 경우, 함수의 원형선언을 구조체 안에 두고 함수의 정의를 밖에서 할 수 있다.

>> ✅ **구조체의 함수는 모든 구조체 변수에 대하여 별도로 존재하는 것이 아닌 하나의 함수를 공유한다.** 
