- ### 1. 상속의 문법적 이해
  <br>
  
  #### 1) 상속의 정의 및 방법 
<div align="left">
  <img src="https://github.com/user-attachments/assets/e9ee1ce7-8502-4a43-b127-4b8a444fe705" height="500" width="700">
</div>

>> ✅ **클래스 상속의 의미란 A 클래스가 B 클래스를 상속하게 되면 A클래스는 B클래스가 지니고있는 모든 멤버를**
>>
>> **물려받게 되는 것을 의미한다.**

>> ✅ **상속의 대상이 되는 B 클래스를 상위/기초/슈퍼/부모 클래스라 호칭하고 상속을 하는 A 클래스를**
>>
>> **하위/유도/서브/자식 클래스라고 부른다.** 

>> ✅  **위의 예제에서 UnivStudent 클래스는 Person 클래스를 상속한다는 문법적 의미로 UnivStudent 클래스 선언**
>>
>> **오른쪽에 `: public Person`이라는 문장을 넣었다.**

>> ✅ **UnivStudent 클래스는 Person 클래스의 private 멤버변수에 접근 할 수 없다. 객체를 기준으로 보면**
>>
>> **Person 클래스의 멤버를 모두 포함하고 있어 가능해보이지만, `접근 제한의 기준은 클래스이기 때문에` UnivStudent**
>>
>> **클래스의 내부 멤버함수에서는 Person의 private 멤버변수에 대한 접근이 불가능하다.**

>> UnivStudent 클래스의 멤버함수 WhoAreYou() 정의 안에서 WhatYourName 과 HowOldAreYou인 Person 클래스의
>>
>> 멤버함수가 호출 가능한것으로 보아 UnivStudent 클래스가 Person 클래스를 상속받았음을 다시 확인할 수 있다.

 #### 2) 유도 클래스의 생성자 정의 

<div align="left">
  <img src="https://github.com/user-attachments/assets/2254a08b-05e4-4532-8c78-8608c4439ad6" height="200" width="500">
</div>

<div align="left">
  <img src="https://github.com/user-attachments/assets/4026c188-6dad-4d44-8a32-b47911dc4cca" height="250" width="400">
</div>

>> ✅ **유도 클래스는 기본 클래스의 멤버를 모두 포함하기 때문에 유도 클래스의 생성자에서 기본 클래스의**
>>
>> **멤버를 초기화해야할 의무가 있다.**

>> 위의 UnivStudent 클래스 생성자 정의를 보게되면 이니셜라이저로 Person 클래스의 생성자를 명시적으로 호출하고
>>
>> 인자로 전달받은 myname, myage 변수를 통해 Person 클래스의 멤버변수를 초기화해야한다.

 #### 3) 유도 클래스의 객체 생성 과정 
 
<div align="left">
  <img src="https://github.com/user-attachments/assets/cbb423ac-7bab-4551-823e-8beb2aa62e53" height="550" width="800">
</div>

>> ✅ **유도 클래스의 객체 생성과정에서 기초 클래스의 생성자는 100% 호출된다.**
 
>> ✅ **위 소스코드의 실행결과를 보면 SoDerived dr1;, SoDerived dr2(12); 의 경우 유도 클래스의 생성자에서** 
>>
>> **기초 클래스의 생성자를 명시적으로 호출하지 않더라도 void형 생성자가 호출되는 것을 알 수 있다.**

<div align="left">
  <img src="https://github.com/user-attachments/assets/80ab22f3-072c-4ef1-91d3-0e3a8c8415ab" height="480" width="800">
</div>

>> SoDerived dr3(23, 24); 문장을 통해 기초 클래스의 생성자 호출 과정을 살펴보면
>>
>> 매개변수 n1, n2 를 인자로 받는 SoDerived 생성자가 호출이 되며, 이니셜라이저를 통해 기초클래스 SoBase 생성자가
>>
>> 호출되며 n1 인자로 초기화 된다. 이로 인해 기초 클래스 멤버변수가 먼저 초기화가 되고 아직 실행이 끝나지 않은
>>
>> 유도 클래스의 생성자 실행이 완료되면서 유도 클래스의 멤버변수도 초기화가 완료된다.

 #### 4) 유도 클래스 객체의 소멸과정 

<div align="left">
  <img src="https://github.com/user-attachments/assets/d2ff77a6-fae2-4a97-8207-09600a940a66" height="400" width="400">
</div>

<div align="left">
  <img src="https://github.com/user-attachments/assets/923c5eff-e2ae-4339-98d6-1d52c0a30d35" height="150" width="400">
</div>

<div align="left">
  <img src="https://github.com/user-attachments/assets/7adeebc9-dbf9-4c1e-83df-790d9b231306" height="150" width="300">
</div>

>> ✅ **유도 클래스의 객체가 소멸될 때에는, 유도 클래스의 소멸자가 실행되고 그 다음에 기초 클래스의 소멸자가**
>>
>> **실행된다. 스택에 생성된 객체의 소멸순서는 생성순서의 역순이다.**

>> 위 예제의 실행결과를 보면 유도 클래스의 소멸자가 호출된 후 기초 클래스의 소멸자가 호출되는 것을 알 수 있다.

<div align="left">
  <img src="https://github.com/user-attachments/assets/86b13597-c88b-4a85-a9f7-a0d0fcf589f4" height="400" width="550">
</div>

>> ✅ **생성자에서 동적할당된 메모리 공간은 소멸자에서 해제해야한다.**

>> UnivStudent 클래스와 Person 클래스의 소멸자는 각자 생성자에서 할당한 메모리 공간을 해제하도록 정의하였다.
>>
>> 기초 클래스와 유도 클래스 모두 소멸자가 호출되니 각자의 소멸자에서 멤버변수에 대한 동적할당된 메모리 공간을
>>
>> 해제하도록 짜여져있는 것을 확인할 수 있다. 
