// 2000 Tehran: Lazy Math Instructor
// ACM-ICPC Live Archive 2056
// POJ 1686

#include <cstdio>
#include <stack>
using namespace std;

char s[1000];
void calc(stack<char> &operators, stack<int> &numbers){
	while (!operators.empty()){
		char op = operators.top();
		operators.pop();
		int num2 = numbers.top();
		numbers.pop();
		int num1 = numbers.top();
		numbers.pop();

		if (op == '+') numbers.push(num1 + num2);
		else if (op == '-') numbers.push(num1 - num2);
		else numbers.push(num1 * num2);
	}
}

int getValue(char *s, int &i){
	stack<char> operators;
	stack<int> numbers;
	while (s[i]){
		if (s[i] == '('){
			i++;
			numbers.push(getValue(s, i));
		}
		else if (s[i] == ')' || s[i] == 0)
			break;
		else if (s[i] == '+' || s[i] == '-'){
			calc(operators, numbers);
			operators.push(s[i]);
		}
		else if (s[i] == '*')
			operators.push(s[i]);
		else if ('a' <= s[i] && s[i] <= 'z' || 'A' <= s[i] && s[i] <= 'Z')
			numbers.push(s[i] - 'A');
		else if ('0' <= s[i] && s[i] <= '9')
			numbers.push(s[i] - '0');
		i++;
	}

	calc(operators, numbers);
	return numbers.top();
}


int main(){
	int T, idx, v[2];
	scanf("%d\n", &T);
	while (T--){
		for (int i = 0; i < 2; i++){
			gets(s);
			idx = 0;
			v[i] = getValue(s, idx);
		}
		puts(v[0] == v[1] ? "YES" : "NO");

	}
	return 0;
}
