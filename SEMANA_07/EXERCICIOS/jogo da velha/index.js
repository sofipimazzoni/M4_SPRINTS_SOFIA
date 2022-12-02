const express = require('express');
const app = express()
const path = require('path');
let x = "f";
let o = "f";

const PORT = 5500;
const localhost = '127.0.0.1:'

app.use(
    express.urlencoded({
        extended: true,
    })
)
app.use(express.json())

const cors = require("cors");
app.use(
    cors({
        origin: "*",
    })
)

app.use(express.static("./front-end"))

app.get("/", (req, res) => {
    res.sendFile(path.join(__dirname, "./front-end/jogo_velha.html"));
})

app.get("/winner", (req, res) => {
    res.send({x, o});
})

app.post("/winner", (req, res) => {
    const {x_final, o_final} = req.body;
    x = x_final;
    o = o_final;
})

app.listen(PORT, () => {
    console.log(`Page server runing at http://${localhost}${PORT}/`)
})
