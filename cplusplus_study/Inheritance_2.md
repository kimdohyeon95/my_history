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

<br>

- ### 3. 상속을 위한 조건
<br>

 #### 1) IS-A 
<div align="left">
  <img src="https://github.com/user-attachments/assets/dacdc17b-84da-4267-b0d4-3230dd1a2407" height="400" width="700">
</div>

>> ✅ **상속의 조건은 기본적인 기능은 공통적이면서, 상속을 하게되는 클래스에서 고유한 특성이 추가되는 것이다.**

>> ✅ **이러한 조건이 성립하기 위해서는 기초 클래스와 유도 클래스 사이에 IS-A(일종의 ~이다.) 관계가 성립되어야한다.**

 #### 2) HAS-A
 
<div align="left">
  <img src="https://github.com/user-attachments/assets/a3d0c401-ae0e-47b7-a4ed-d6fb0c8e8582" height="350" width="600">
</div>

>> ✅ **상속의 조건은 HAS-A관계 처럼 ~을 가지다라는 소유의 관계도 표현할 수 있다.**

>> 위의 예제는 Gun 클래스를 Police 클래스가 상속받아 Police 객체 생성 시, 총알 수와 수갑의 갯수로 생성자를 초기화
>>
>> 하여 경찰이 총을 소유한다는 HAS-A 관계를 표현하고 있다.

>> HAS-A 관계의 상속은 소유하고 있지 않을 때를 표현하기 애매한 부분이 있고 여러가지를 소유하는 경우에 다중상속으로 인해
>>
>> 프로그램이 더 복잡해질 수 있다는 단점이 있다.

>> ✅ **따라서 상속의 조건에는 HAS-A 관계 보다 IS-A 관계가 더욱 적합하다고 볼 수 있다.**
