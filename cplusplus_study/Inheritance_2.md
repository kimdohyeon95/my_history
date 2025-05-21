- ### 1. protected 선언
<br>

<div align="left">
  <img src="https://github.com/user-attachments/assets/3294c6f9-3ace-4206-93fc-74fd72053932" height="350" width="650">
</div>

>> 위 예제의 Base 클래스의 멤버는 private/protected/public 세가지 형태의 접근제어 지시자가 존재한다.
>>
>> 이중에서 private 과 protected 는 Base클래스에서 봤을 때는 차이가 존재하지 않는다.
>>
>> 하지만 Base 클래스가 Derived 클래스를 상속하게 되면 protected로 선언된 멤버변수는 Derived 클래스
>>
>> 내에서 사용이 가능하다.

>> ✅ **요약하면 protected로 선언된 멤버변수는 이를 상속하는 유도 클래스에서 접근이 가능하다.**

>> 그러나, 기초 클래스와 유도 클래스 사이에서도 정보은닉은 지켜지는게 좋다.

<br>

- ### 2. 세가지 형태의 상속

<div align="left">
  <img src="https://github.com/user-attachments/assets/cd77fb95-35c1-43b2-8ea8-dd910eab214c" height="400" width="650">
</div>

<div align="left">
  <img src="https://github.com/user-attachments/assets/e2d4e75a-455b-4c1e-a374-0b656741fdb9" height="300" width="350">
</div>

>> 위의 예제에서 Base 클래스를 상속받은 Derived 클래스의 객체를 생성하고 상속받은 멤버변수 num3를
>>
>> drv.num3 를 통해 main문에서 접근하려고 하면 에러가 발생한다.

>> 그 이유는 Base 클래스에서 public 형태로 선언하였으나 Derived 클래스에서 protected 형태로 상속
>>
>> 받았기 때문에, Derived 클래스 내부에서만 접근할 수 있고 클래스 외부에서는 접근이 제한되어있기 때문이다.

- ### 3. 상속을 위한 조건
<br>

<div align="left">
  <img src="https://github.com/user-attachments/assets/dacdc17b-84da-4267-b0d4-3230dd1a2407" height="400" width="700">
</div>

>> ✅ **상속의 조건은 기본적인 기능은 공통적이면서, 상속을 하게되는 클래스에서 고유한 특성이 추가되는 것이다.**

>> ✅ **이러한 조건이
