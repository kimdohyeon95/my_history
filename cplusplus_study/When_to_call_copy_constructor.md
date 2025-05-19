- ### 1. 복사 생성자의 호출 시점

<br>
<p align="left">  
  <img src="https://github.com/user-attachments/assets/90688918-1455-4376-9a6b-4dbaeb60d73c" width="40%"height="480">  
  <img src="https://github.com/user-attachments/assets/464220cf-39f3-40c7-a462-403b7ff29a72" width="40%" height="480">
</p>

<div align="left">
  <img src="https://github.com/user-attachments/assets/54578f44-f477-4316-beb5-69482b088a0d" height="120" width="350">
</div>

>> ✅ **복사 생성자의 호출 시점은 1.기존에 생성된 객체를 이용해서 새로운 객체를 초기화 하는 경우**

>> ✅ **2. Call-by-value 방식의 함수호출 과정에서 객체를 인자로 전달하는 경우**

>> ✅ **3. 객체를 반환하되, 참조형으로 반환하지 않는 경우 이 3가지가 있다.**

>> 첫번 째 경우는 `SoSimple sim2 = sim1;` 문장과 같은 경우라고 볼 수 있다.

>> 두 세번째 경우는 위의 예제 main문 안의 SimpleFuncObj(obj) 호출 과정에서 SimpleObj 함수의 매개변수 ob에 인자로
>>
>> obj객체를 전달하고 있다. 이 때 ob 객체의 복사 생성자가 호출 되면서 obj객체로 초기화 된다.
>>
>> 그 다음, return ob; 문장에서 ob 객체를 반환할 때, 임시 객체라는 것이 생성되고 이 임시객체의 복사 생성자가 호출
>>
>> 되면 그것의 인자로 ob객체가 전달된다. 결과적으로 지역적으로 선언된 객체 ob는 소멸되고 obj 객체와 임시객체만 남는다.
>>
>> 반환된 임시객체가 AddNum함수를 호출하여 임시객체의 num값이 30증가하고 이어서 ShowData 함수를 통해 임시객체에
>>
>> 저장된 num값이 출력되고있다. 또한 그 뒤의 obj 객체를 통해 ShowData함수를 호출 하는데 임시객체의 ShowData함수와
>>
>> obj 객체의 ShowData함수 호출을 통해 나온값은 서로 다르고 이는 두 객체가 서로 별개임을 의미한다.
<br>

### 2. 임시 객체의 소멸 시점
