const fs = require('fs') 
const express = require('express')
const bodyParser = require('body-parser');
const cors = require('cors');
const app = express();
const port = 3000;

// Where we will keep books
let db = [];

app.use(cors());

// Configuring body parser middleware
app.use(bodyParser.urlencoded({ extended: false }));
//app.use(bodyParser.json());
    app.get('/:lat/:long/:time/:noise', (req, res) => {
    const lat = req.params.lat; 
    const long= req.params.long;
    const time = req.params.time;
    const noise = req.params.noise;
    ob=lat+","+long+","+time+","+noise+"\n";
    // Output the book to the consoles d debugging
    console.log(typeof ob);
    db.push(ob);
    fs.appendFileSync('samplefile.txt', ob, (err) => { 
      
    // In case of a error throw err. 
    if (err) throw err; 
}); 
    res.send('data is added to the database');
});

app.get('/', (req, res) => {
    fs.readFile('samplefile.txt','utf-8',(err, data) => { 
    if (err) throw err;   
    // Converting Raw Buffer to text 
    // data using tostring function. 
    console.log(data); 
}) ;
});
app.listen(port, () => console.log(`Hello world app listening on port ${port}!`));
