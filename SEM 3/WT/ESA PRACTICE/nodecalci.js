const http = require('http');
const url = require('url');

http.createServer((req, res) => {
    if (req.method === 'GET') {
        const query = url.parse(req.url, true).query;
        const { op, op1, op2 } = query;
        const num1 = parseFloat(op1);
        const num2 = parseFloat(op2);
        let result;

        switch (op) {
            case 'add':
                result = num1 + num2;
                break;
            case 'subtract':
                result = num1 - num2;
                break;
            case 'multiply':
                result = num1 * num2;
                break;
            case 'divide':
                result = num1 / num2;
                break;
            default:
                result = 'Invalid operation';
        }

        res.writeHead(200, { 'Content-Type': 'text/plain' });
        res.end(`Result: ${result}`);
    }
}).listen(8000, () => console.log('Server running on http://localhost:8000'));
