var arr = [];
let sentence = '';

function disp(element) {
    document.getElementById('display').innerHTML = element
}

function app(x) {
    arr.push(x);
    sentence+=x
    disp(sentence);
    // console.log('x ' + x );
}

function backspace() {
    arr.pop();
    let sentence2 = "";
    for (let i=0;i<(sentence.length-1);i++) {
        sentence2 += sentence[i]
    }
    sentence = sentence2
    console.log(sentence);
    disp(sentence);
}

function solve(num1, oper, num2) {
    if (oper==undefined) {
        return num1
    }
    switch (oper) {
        case '+':
            return num1+num2;
        case '-':
            return num1-num2;
        case 'x':
            return num1*num2;
        case '÷':
            return num1/num2;
        case '⅟':
            return num1 + 1/num2;
        case '²':
            if (num2!=0)
                return num1*num1*num2;
            else
                return num1*num1
        case '√':
            if (num1!=0)
                return num1*Math.sqrt(num2);
            else
                return Math.sqrt(num2);
        case '~':
            if (num1!=0)
                return num1*(~num2)
            else
                return ~num2
        default:
            console.log("Operant doesn't exist");
            alert("Operant doesn't exist");
            return ;
        }
}

function clear_button() {
    let l = arr.length;
    arr = [];
    sentence = '';
    disp('0');
}

function read_line(i,a) {
    let b,c=0;
    if (arr[i]==undefined) {
        return solve(a,b,c);
    }
    else {
        b=arr[i];
        i++
        for (i;typeof(arr[i])==='number';i++) {
            c = (c*10 + arr[i]);
        }
        c = read_line(i,c);
        return solve(a,b,c);
    }
}

function add_to_log(question,answer) {
    if (document.getElementById("log").innerHTML == "Empty") {
        document.getElementById("log").innerHTML = question + "=" + answer;
    }
    else if(question == answer) {
        return
    }
    else {
        document.getElementById("log").innerHTML += "<br>" + question + "=" + answer;
    }
}

function compute() {

    let a=0;
    let i=0;
    for (i;typeof(arr[i])==='number';i++) {
        a = (a*10 + arr[i]);
    }

    let to_solve = sentence;
    sentence = read_line(i,a);
    disp(sentence);
    arr = []
    arr[0] = sentence;
    sentence = sentence.toString();
    let ans = sentence;
    add_to_log(to_solve,ans);
}

function ch_log_disp() {
    if (document.getElementById("log").style.display != "none") {
        document.getElementById("log").style.display = "none";

    }
    else {
        document.getElementById("log").style.display = "block";

    }
}