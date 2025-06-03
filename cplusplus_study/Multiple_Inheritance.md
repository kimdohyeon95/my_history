- ### 다중상속에 대한 이해
  <br>
 #### 1) 다중상속의 모호성

<div align="left">
  <img src="https://github.com/user-attachments/assets/1405f0fb-0a4f-40fb-8f70-5667abbf3422" height="350" width="500">
</div>

>> 위 예제는 BaseOne 클래스와 BaseTwo 클래스를 상속 받는 MultiDerived 클래스를 나타낸 것이다.
>>
>> main문 안에서 MultiDerived 객체를 생성한 후 ComplexFunc() 함수를 호출하게 되면 내부에 있는
>>
>> SimpleFunc() 함수를 호출하는 문장이 있다.

>> ✅ **이 때, BaseOne, BaseTwo 기초 클래스 둘다 멤버함수로 SimpleFunc() 함수를 가지고 있기 때문에,**
>>
>> **어느 클래스의 함수를 호출할 것인지 명시해야 실행이 가능하다.**

 #### 2) 가상 상속 (Virtual Inheritance) 
 
<div align="left">
  <img src="https://github.com/user-attachments/assets/07114972-1285-4a34-ae28-d968c4c120c9" height="500" width="750">
</div>

>> 위 예제는 Base 클래스를 상속하는 MiddleDerivedOne 클래스와 MiddleDerivedTwo 클래스가 존재한다.

>> 그리고 MiddleDerivedOne 클래스와 MiddleDerivedTwo 클래스를 다중상속하는 LastDerived 클래스가
>>
>> 있다. **MiddleDerivedOne 클래스와 MiddleDerivedTwo 클래스가 Base 클래스를 virtual 키워드를**
>>
>> **사용하지 않고 그냥 일반상속 하게되면 LastDerived 객체가 생성 될 때, 두 개의 Base 클래스 멤버가**
>>
>> **존재하게 된다.**

>> **따라서, LastDerived 클래스의 멤버함수 ComplexFunc() 함수를 호출할 때, 몸체 내부의 SimpleFunc()**
>>
>> **함수 호출 문장 실행 시, MiddleDerivedOne::SimpleFunc(); 문장처럼 어느 클래스를 통해서 간접 상속한**
>>
>> **Base 클래스의 멤버함수를 호출할 것인지 명시해야한다.**

<div align="left">
  <img src="https://github.com/user-attachments/assets/af424dac-9386-4a51-b11b-0ca986cfa286" height="500" width="650">
</div>

>> **이러한 문제를 해결하기 위해, class MiddleDerivedOne: virtual public Base**
>>
>> **class MiddleDerivedTwo: virtual public Base 과 virtual 키워드를 넣어 가상 상속을 해준다.**

>> **이렇게 함으로써 위 이미지에서 나오듯, LastDerived 객체 내에는 MiddleDerivedOne 클래스와 MiddleDerivedTwo**
>>
>> **클래스가 동시에 상속하는 Base 클래스의 멤버가 하나씩만 존재한다.**

>> **그래서 LastDerived 클래스의 멤버함수 ComplexFunc() 함수 안에서 SimpleFunc() 함수 이름만 가지고 호출 가능하다.**

<div align="left">
  <img src="https://github.com/user-attachments/assets/54a2a296-ac0c-4d1a-8556-8571a4d6f785" height="350" width="350">
</div>

<div align="left">
  <img src="https://github.com/user-attachments/assets/93066e0a-81ca-4467-879d-cbd59db5c5d2" height="350" width="350">
</div>

<div align="left">
  <img src="https://github.com/user-attachments/assets/366ce170-f8d1-4137-b52b-0c2dd394eab3" height="150" width="350">
</div>

<div align="left">
  <img src="https://github.com/user-attachments/assets/072fce28-0f68-4c9b-84d7-7702f37adac7" height="200" width="300">
</div>

>> 코드의 실행 결과를 보게 되면 가상 상속으로 인해 Base 클래스의 생성자가 한번만 호출되는 것을 확인할 수 있다.

>> 만약 가상 상속을 하지 않게 되면, Base 클래스의 생성자가 두번 호출 된다.                         
