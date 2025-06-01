- ### 1.순수 가상함수와 추상 클래스
<br>

  #### 1) 순수 가상함수(Pure Virtual Function)와 추상 클래스(Abstract Class) 설명

<div align="left">
  <img src="https://github.com/user-attachments/assets/fda456df-bc4f-4f66-bdc5-63f76c84ecba" height="350" width="500">
</div>

>> ✅ **클래스 중에서는 객체의 생성을 목적으로 정의 되지 않는 클래스가 존재하는데 이를 추상 클래스라고 한다.**
>>
>> **이러한 추상 클래스는 객체의 생성이 불가능하다.**

>> ✅ **추상 클래스 안에는 순수 가상함수가 1개 이상이 포함되어 있는 것을 의미하고 이러한 순수 가상함수는** 
>>
>> **함수의 몸체가 정의되지 않은 함수를 의미한다.**

>> ✅ **순수 가상함수는 함수 선언 시 앞에 virtual 키워드를 붙이고 선언 뒤에 `=0`의 대입을 통해**
>>
>> **명시적으로 몸체를 정의하지 않았음을 컴파일러에게 알린다.**

 #### 2) 다형성(Polymorphism)

<div align="left">
  <img src="https://github.com/user-attachments/assets/66ca8983-aeb7-450f-812d-7414e9f5ff95" height="350" width="530">
</div>

>> ✅ **다형성이란 동질이상을 의미하고, 모습은 같은데 형태는 다르다는 의미이다.**
>>
>> **다형성의 예시로 위의 예제에서 ptr->SimpleFunc(); 문장이 2번 등장한다. ptr은 동일한 포인터**
>>
>> **변수임에도 참조하는 객체의 자료형이 다르기 때문에 실행 결과도 달라지게 된다.**
