const fs = require('node:fs');
const content = '000000000000000000000000000000000000000000000000000000000000000'
try {
  fs.writeFileSync('output.txt', content, {flag: 'a+'});
}
catch(err){
  console.log(err);
}