- ### 1. namespace의 선언과 정의
<br>

<div align="left">
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="https://github.com/user-attachments/assets/59326448-289d-42fc-a9a4-09b39e136840" height="400" width="480">
</div>

<br>

>> 위의 예시는 이름공간 BestComImpl과 ProgComImpl에 위치하는 함수 SimpleFunc의 선언과 정의를 분리한 것이다.

>> ✅ **함수 정의 시, 이름공간 다음에 `범위 지정연산자 ::`을 사용하여 어느 이름공간에 속해있는지를 나타낸다.** 
<br>


- ### 2. 동일한 namespace 내에서의 함수 호출
<br>

<div align="left">
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="https://github.com/user-attachments/assets/4b4a0a7d-a27e-4086-9caa-37094ef4dbed" height="150" width="300">
</div>

<div align="left">
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="https://github.com/user-attachments/assets/f5c88d41-2fbd-4f21-b69e-e07305fd63b4" height="200" width="400">
</div>

<br>

>> 선언된 이름공간의 이름이 동일할 때 이들은 동일한 이름공간으로 간주된다. 위의 예시에서 SimpleFunc 와 PrettyFunc는
>> 동일한 이름 공간안에 존재하는 상황이다.

>>✅ **이름공간을 명시하지 않고 함수를 호출하면, `함수의 호출문이 존재하는 함수와 동일한 이름공간 내에서`**
>>**호출할 함수를 찾게 된다.** 따라서 SimpleFunc 함수 내에서는 이름공간을 명시하지 않은 상태에서
>>PrettyFunc 함수를 직접호출 할 수 있다.
<br>


- ### 3. using을 이용한 namespace 명시
<br>

<p align="left">  
  <img src="https://github.com/user-attachments/assets/0ea2c03d-dce2-45c3-bd17-9de4bacfeb2c"  width="32%">  
  <img src="https://github.com/user-attachments/assets/3da69542-4eb1-4f14-b19a-b9a6cb27641d"  width="32%">
</p>


>> using 키워드를 사용하여 `using std::cin` 과 같이 맨 윗부분에 선언하면, cin 함수로만 써서 사용할 수 있고,  
>> std 이름공간내의 cin 함수를 호출 한다는 의미와 같다.

>> 또다른 방법으로는 `using std` 를 선언하는 방법이있다. 이것은 std 이름공간안에 있는 함수들을 호출할 때에는
>> 앞에 std 이름공간 선언 없이 접근하겠다는 의미이다.  
<br>


- ### 4. namespace의 별칭 지정과 전역변수의 접근
<br>

<div align="left">
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="https://github.com/user-attachments/assets/217da0e9-bb2f-4e5b-8530-d3ec6d3920df" height="300" width="350">
</div>

<br>

>> 이름공간안에 또다른 이름공간이 여러개 겹쳐져 있을 때, 별칭을 지정할 수 있다.

>> ✅ **`namespace ABC=AAA::BBB::CCC;` 와 같이 AAA::BBB::CCC 라는 이름공간에 ABC라는 별칭을 붙인다.**

>> ✅ 그후 `ABC::num1 = 10; ABC::num2 = 20;` 과 같이 선언한 별칭 ABC로 이름공간안의 변수에 접근 할 수 있다.
