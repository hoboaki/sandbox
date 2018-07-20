
window.onload = function() {
    const content = document.getElementById('content');
    let text = "";

    text += "<input id=\"JsonReadTestBtn\" type=\"button\" value=\"JsonReadTestBtn\"/>\n";
    content.innerHTML = text

    document.querySelector('#JsonReadTestBtn').addEventListener('click', onJsonReadTestBtnClicked)
}

function onJsonReadTestBtnClicked() {
    const dialog = require('electron').remote.dialog;
    const filenames = dialog.showOpenDialog(null, {
        properties: ['openFile'],
        title: 'Select a json file',
        defaultPath: '.',
        filters: [
            {name: 'json file', extensions: ['json']}
        ]
    });
    if (filenames.length == 0) {
        return;
    }

    const fs = require('fs')
    const filepath = filenames[0];
    fs.readFile(filepath, 'utf-8', (err, data) => {
        if(err){
            alert("An error ocurred reading the file :" + err.message);
            return;
        }
        const jsonData = JSON.parse(data);
        console.log(jsonData);
        alert("Data length is " + data.length + ".");
    });
}
