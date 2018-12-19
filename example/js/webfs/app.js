var express = require('express');
var path = require('path');
var logger = require('morgan');
var fs = require('fs')

// TODO: Parse from external json file.
var CONFIG = {
    port: 8080,
    root: process.env['HOME']
};

var app = express();

app.set('view engine', 'ejs');
app.set('views', path.join(__dirname, 'views'));

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(express.static(path.join(__dirname, 'public')));

app.get('/*', function(request, response) {
    var server_path = path.join(CONFIG.root, request.path)
    var status = fs.statSync(server_path)
    if (status.isFile())
        return response.sendFile(server_path)

    if (status.isDirectory()) {
        return response.render('directory', {
            path: request.path,
            back: path.dirname(request.path),
            files: fs.readdirSync(server_path),
        });
    }

    response.statusCode = 404
    response.send("Not found")
});

app.listen(CONFIG.port, function() {
    console.log('Running on ' + CONFIG.port)
});