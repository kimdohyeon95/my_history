- ### 1. Class Information hiding (클래스 정보 은닉)
<br> 

<p align="left">  
  <img src="https://github.com/user-attachments/assets/ec394986-4db1-4811-ad43-9f2989eb5e15" width="40%" height="350">  
  <img src="https://github.com/user-attachments/assets/8ccbafaf-25e0-4a98-896e-02421f461fb1" width="40%" height="350">
</p>

>> ✅ **클래스에서 정보은닉이란 `멤버변수를 private형태로 선언하고` 외부에서 클래스의 `내부 멤버변수에`**
>>
>> **`접근할 때 해당 멤버변수에 접근하는 public함수를 별도로 정의해서` 안전한 형태로 멤버변수에 접근을 유도하는 것이다.**

>> ✅ 제한된 방법으로의 접근만을 허용해서 잘못된 값이 저장되지 않도록 돕거나 예외처리를 넣어서 실수를 했을 때
>> 
>> 쉽게 발견하도록 도와주는 역할을 한다.

>> ✅ **클래스 내에서 getXXX 형식의 이름으로 정의된 함수들은 클래스 외부에서 private 형태로 선언된 멤버변수의 값을**
>>
>> **접근하기위한 목적으로 정의되는 함수들이다. `const 키워드가 들어가있어서 함수 내부에서는 멤버변수의 값을 변경하지`**
>> 
>> **않겠다`는 의미를 내포한다.**

>> ✅ **또한 const 함수 내에서 const 키워드가 붙지않은 함수를 호출하는 것 또한 컴파일 에러를 발생시킨다.**

<br>

- ### 2. Class Encapsulation (클래스 캡슐화)
<br>
<p align="left">  
  <img src="https://github.com/user-attachments/assets/d5d2a3b3-af47-4e2d-8c25-1e2d4c2f79a7" width="40%" height="500">  
  <img src="https://github.com/user-attachments/assets/892afc0a-8feb-427b-9f14-c75e17ada249" width="40%" height="500">
</p>

>> ✅ **클래스의 캡슐화란 서로 관련있는 함수와 변수를 하나의 클래스 안에 묶는 것을 의미한다.**

>> 위의 예제에서 왼쪽의 콧물,재채기,코막힘을 치료하는 클래스를 각각 분리하여 ColdPatient 클래스에서 개별호출 하고 있다.
>>
>> 이와 같은 경우 캡슐화가 되어있지 않기 때문에 프로그램이 복잡해지고 특정 순서를 요구하는 경우라면 상당히 비효율적이다.

>> 따라서 오른쪽 예제 처럼 콧물, 재채기, 코막힘 3개의 클래스 객체를 CONTAC600이라는 클래스 안에 멤버변수로 두고
>>
>> ColdPatient 클래스의 내부 멤버함수에서 캡슐화된 CONTAC600 클래스의 객체를 호출하는 식으로 변경하면 효율적인 구성을
>>
>> 할 수 있다.   
