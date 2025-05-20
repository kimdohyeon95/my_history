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
