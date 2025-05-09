- ### 1. reference(참조자) 의 이해 
<br> 

<p align="left">  
  <img src="https://github.com/user-attachments/assets/2256a116-97ca-4c44-8092-af282bc934b5" width="40%">  
  <img src="https://github.com/user-attachments/assets/0ec6e0a2-98f9-4237-921a-7c273987dcac" width="40%" height="250">
</p>


>> 변수의 선언을 할 때, 변수명의 이름으로 메모리 공간이 할당 되는데, 참조자를 이용하여
>>  변수에 또다른 별명을 붙일 수 있다.

>> ✅ **`변수 선언 시, 참조자 &`를 붙여서 참조자를 선언 할 수 있다.**
<br>

- ### 2. 포인터 변수 대상의 참조자 선언
  <br>

<div align="left">
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="https://github.com/user-attachments/assets/9fcc3849-6d4a-45da-9228-0d5be5a6dad1" height="250" width="300" >
</div>

>> 참조자는 일반 변수 뿐만 아니라 포인터 변수에 대해서도 참조자 선언이 가능하다.

>> ✅ **일반 변수의 참조자 선언과 동일하게 `포인터 변수 선언 방식에서 포인터 변수 앞에 참조자 &를 붙여서` 선언한다.**
<br>

- ### 3. Call-by-reference의 위험성과 const 참조자
<br>

<div align="left">
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="https://github.com/user-attachments/assets/6d294fef-b68a-4fae-98b1-86337c9e6f47" height="150" width="500" >
</div>

>> C언어에서는 참조자가 존재 하지 않으므로, 지역변수로 선언한 변수의 값을 인자로 넘겨주어도 값에 의한 호출이기 때문에
>> 지역변수의 값이 변경되지 않는다.

>> 그러나, C++에서 HappyFunc 함수의 매개변수를 참조 변수로 정의할 경우, 미리 정의된 지역변수의 값이 바뀔수도 있다.

>> 이는 코드가 복잡해지면, 함수 호출문 만을 보고서는 값이 변경되는지 모르기 때문에 값의 변경 여부를 알기 위해서는
>> 몸체까지 분석해야한다.

>> ✅ **따라서 함수 정의 시, 참조자에 의한 값의 변경을 하지 않겠다는 것을 알리기위해 `const` 키워드를 붙이는 것이 좋다.**
<br>

- ### 4. 함수의 반환형이 참조형(Reference Type)인 경우
<br>

  #### 1) 반환형을 받는 변수가 참조 변수일 경우
<p align="left">
  <img src="https://github.com/user-attachments/assets/34607fe5-41f1-4f36-bf29-a1d59bb7fd17"  width="35%" >
  <img src="https://github.com/user-attachments/assets/19a84ccd-6c17-42e6-8622-3a4b676865b7"  width="50%" height="320">
</p>


>> 위의 예제에서 RefRetFuncOne함수의 반환형은 참조형이다. 이때, main문의 지역변수 num1이 인자로 넘어가면서 ref 참조자는
>> num1을 가리킨다.

>> ✅ **RefFuncOne 함수가 종료될 때 ref 참조자는 소멸되나 ref가 가리키는 변수는 소멸 되지 않으므로 참조자 num2가 
>> num1을 가리키게된다.**

   #### 2) 반환형을 받는 변수가 일반 변수일 경우 
<p align="left">
  <img src="https://github.com/user-attachments/assets/9e8f9186-5a67-468f-817b-39656f59ec78"  width="35%" >
  <img src="https://github.com/user-attachments/assets/725fdfc3-aff2-452a-8d4e-8b3ed82a843b"  width="50%" height="320">
</p>


>> 위의 예제에서는 RefRetFuncOne 함수의 반환형을 일반변수로 받는다. 이때, 함수의 종료 후 반환형을 받는 변수 num2는
>> 참조 변수가 아니므로 그냥 값만을 받게 된다.

>> ✅ **따라서, num1과 num2는 둘다 다른 변수로 분리가된다.**
<br>

- ### 5. 상수를 참조하는 참조자
<br>
<div align="left">
  <img src="https://github.com/user-attachments/assets/528501a5-a02b-4817-9832-8da834bbe65d" height="150" width="35%" >
  <img src="https://github.com/user-attachments/assets/222865b6-97fa-4fa0-9d3b-b763742d4da5" height="150" width="35%" >
</div>

>> ✅ **const 키워드를 통해서 상수화된 변수들은 어떤 경로를 통해서라도 값의 변경이 일어나서는 안된다. 만약 이를 어길 경우
>> C++에서는 에러를 발생 시킨다.**

>> 따라서 상수화된 변수에 대한 참조자를 선언하는 경우에도 앞에 const 키워드를 붙여주어야 한다.

>> ✅ **참조 변수는 선언시 변수만을 참 할 수 있지만 앞에 const 키워드를 붙여서 상수를 참조할 때 `임시변수`를 만들어
>> 이 장소에 상수를 저장하고 참조자가 이를 참조 가능하도록 한다.**
