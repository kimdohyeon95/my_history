### 1.static 키워드 
<br>

<p align="left">  
  <img src="https://github.com/user-attachments/assets/020cfb15-12df-4021-a425-c32b0a651543" width="40%" height="400">  
  <img src="https://github.com/user-attachments/assets/25402f9c-1a16-4c27-8fc1-498edd1fc5a1" width="40%" height="200">
</p>

<div align="left">
  <img src="https://github.com/user-attachments/assets/4362c0a3-0b51-457c-8225-7fa31e979c07"  width="360" height="200" >
</div>

<div align="left">
  <img src="https://github.com/user-attachments/assets/2e4b09af-3578-421d-9cb4-473d6687e0eb"  width="300" height="100" >
</div>

>> ✅ **static 멤버변수는 `클래스 변수`라고도 한다. 일반적인 멤버변수와 달리 클래스당 하나씩만 생성되기 때문이다.**
>> 
>> ✅ **static 멤버변수를 생성자 안에서 초기화하지 않고 클래스 밖에서 초기화하는 이유는 클래스에 단 한개 밖에 존재하지 않고**
>>
>> **객체가 생성될 때 동시에 생성되는 변수가 아닌 이미 메모리 공간에 할당이 이뤄진 변수이기 때문에 생성자 안에서**
>>
>> **초기화를 할 시 객체가 생성될 때마다 0으로 초기화되기 때문이다.**

>> 위의 예제에서 simObjCnt 와 cmxObjCnt static 변수는 각각 클래스 내의 멤버함수(생성자) 안에서 마치 멤버변수인 것 마냥
>>
>> 사용되는데 그렇다고 이를 멤버변수로 오해하면 안된다.

<br>

### 2. static 멤버변수의 접근방법 
<br>

<div align="left">
  <img src="https://github.com/user-attachments/assets/abf1acaa-ef2a-4e76-8142-f604e6efffd1"  width="360" height="400" >
</div>

<div align="left">
  <img src="https://github.com/user-attachments/assets/05316365-f60e-43ab-acd4-8a4fffaa6c63"  width="300" height="80" >
</div>

>> static 멤버변수를 private 형이 아닌 public 형으로 선언하면 클래스 외부에서 클래스 이름 또는 객체의 이름을 통해
>>
>> 접근이 가능하다.

>> ✅ **위의 예제에서 SoSimple::simObjCnt문장으로 객체를 생성하지 않았음에도 클래스의 이름을 통해서 static 멤버변수에**
>>
>> **접근할 수 있다는 것을 알 수 있다.**

>> ✅ **그러나 객체의 이름을 통해서 static 멤버변수에 접근하는 것은 지양하여야 한다. 왜냐하면 객체의 멤버변수에 접근하는**
>>
>>  **것처럼 보일 수 있기 때문이다.**

>> ✅ **static 멤버함수 역시 static 멤버변수와 그 특성이 동일한데 static 멤버함수 내에서는 static 멤버변수와 함수만을**
>>
>>  **호출 할 수 있다.**
<br>

### 3. const static 멤버 
<br>

<div align="left">
  <img src="https://github.com/user-attachments/assets/abf1acaa-ef2a-4e76-8142-f604e6efffd1"  width="360" height="400" >
</div>

>> 클래스 내에서 const 멤버변수의 초기화는 이니셜라이저를 통해야만 한다.

>> ✅ **그러나 const static으로 선언된는 멤버변수는 객체가 생성되기 전에 이미 메모리 공간을 할당받고 있는 상태이기 때문에**
>>
>> **선언과 동시에 초기화가 가능하다.**
<br>

### 4. mutable 키워드 
<br>

<div align="left">
  <img src="https://github.com/user-attachments/assets/08bd3a89-be62-457f-b1ab-8b4066365e77"  width="360" height="400" >
</div>

<div align="left">
  <img src="https://github.com/user-attachments/assets/dc559e01-bd09-490e-8d0b-15fcb216e23a"  width="200" height="80" >
</div>

>> ✅ **mutable 키워드는 const 함수내에서 값의 변경을 예외적으로 허용한다는 의미이다.**

>> 위의 예제에서 CopyToNUm2() 함수는 const 키워드로 선언되어 있지만 num2=num1 문장처럼
>>
>> num2값의 변경을 허용하고 있는 것을 알 수 있다.

>>  ✅ **단 mutable 키워드의 빈번한 사용은 const 키워드의 중요성을 의미없게 만듦으로 매우 예외적인 경우만 사용하도록 한다.**
