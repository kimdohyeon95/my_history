- ### 1. friend 선언
<br>

  #### 1) class 내에서의 friend 선언 
<div align="left">
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="https://github.com/user-attachments/assets/c5cd6c25-45a9-4608-b525-3edae4412078"  width="380" height="450" >
</div>

<div align="left">
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="https://github.com/user-attachments/assets/93a4c0d8-4c5a-40fe-8cbc-043feca09646"  width="380" height="150" >
</div>

<div align="left">
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="https://github.com/user-attachments/assets/ce94e519-6dd9-4d94-9dfc-31744619a0b3"  width="280" height="80" >
</div>

>> ✅ **friend 선언은 어느 한 클래스가 다른 클래스의 private멤버에 접근이 가능하도록 허용하는 선언이다.**

>> ✅ **friend 선언은 private 혹은 public 어느 영역에 존재하든 상관이 없다.**

>> ✅ **단 friend 선언을 지나치게 하면 정보은닉을 무너뜨리는 문법이 되기 때문에 필요한 상황에서 소극적으로 사용해야한다.**

>> 위의 예제에서 Boy Class와 Girl Class는 서로 friend 선언을 하고 있다.
>>
>> 따라서 각 클래스에 존재하는 ShowYourFriendInfo 함수의 매개변수 Girl &frn / Boy &frn 객체를 가지고
>>
>> 상대 클래스의 private 멤버에 접근이 가능한 것을 알 수 있다.

  #### 2) 클래스 멤버함수 또는 전역함수의 friend 선언 
<div align="left">
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="https://github.com/user-attachments/assets/b3575579-c499-49fe-b1a2-441a511fef0a"  width="380" height="450" >
</div> 

<div align="left">
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="https://github.com/user-attachments/assets/f9c41fed-d8d9-4f6c-95f5-1e2677a99508"  width="380" height="330" >
</div>

<div align="left">
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="https://github.com/user-attachments/assets/7e28f2e0-68d4-4b9e-84e5-4fb2fd66428c"  width="280" height="70" >
</div>

>> ✅ 클래스 멤버함수 또는 전역함수에서 friend 선언된 함수는 자신이 선언된 클래스의 private영역에 접근이 가능하다.

>> 위 예제에서 PointOP 클래스의멤버함수 PointAdd함수와 PointSub함수는 Point 클래스 내에서 friend 선언이 되어있다.
>>
>> ✅ **`따라서 PointAdd 함수와 PointSub 함수의 매개변수 const Point& pnt1 과 const Point& pnt2 객체를 통해`**
>>
>> **`Point클래스의 private 멤버변수 x, y에 직접 접근을 하여 연산이 가능하다.`**
>>
>> 또한 ShowPointPos 함수도 Point 클래스 내에서 friend 선언이 되어있다. 따라서 const Point& pos 매개변수를 통해
>>
>> private 멤버변수 x,y 값을 출력하는 것이 가능하다.

- ### 2. static 
