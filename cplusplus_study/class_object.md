- ### Class 정의와 Object 
<br>
<div align="left">
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="https://github.com/user-attachments/assets/06ebd921-ec2c-4bbf-b1d3-ebafda57acf1"  width="450" height="150" >
</div>

<p align="left">
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="https://github.com/user-attachments/assets/328a5226-0c53-43b9-9467-4d9a767d6c21"  width="35%" height="350">
  <img src="https://github.com/user-attachments/assets/0ed5d794-85c3-43bf-9dec-18545c9d4e6b"  width="35%" height="350">
</p>

>> ✅ C++ 클래스는 구조체 정의한 struct 키워드를 class로 변경하여 정의한 것이다. 클래스 안에 선언된
>> 변수 또는 함수를 멤버변수/멤버함수 라고 한다.

>> ✅ 객체는 하나 이상의 상태정보(데이터)와 하나 이상의 행동(기능)으로 구성이 된 것이다.

>> ✅ **객체를 생성하는 방식에는 `ClassName ObjectName;` 처럼 일반적인 변수 선언 방식과
>> `ClassName *ptrObjectName = new Classname;` 동적 할당 방식이 있다.**  

>> ✅ **클래스 정의 시, 접근제어 지시자 `private, protected, public`가 선언되면 그 이후에 등장하는
>> 변수나 함수는 접근제어 지시자에 해당하는 범위 내에서 접근이 가능하다.**

>> ✅ 그 이후 새로운 접근제어 지시자가 등장하면 그 다음에 등장하는 함수나 변수는 새로운 접근제어 지시자
>> 에 해당하는 범위 내에서 접근이 가능하다.

>> ✅ **클래스 정의 시 선언된 멤버 변수 또는 함수에 별도의 접근제어 지시자를 선언하지 않으면, `private`
>> 으로 선언된다.** 
