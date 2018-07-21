window.onload = function() {
    // コンテンツ入れ物
    let contents = []

    // Json 読み込みテスト
    contents.push({id: "JsonReadTest", label: "JsonReadTest", func: onJsonReadTestBtnClicked})
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
        if (filenames == null) {
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

    // コンテンツ展開
    const contentElem = document.getElementById('content');
    let text = "";
    contents.forEach(function(entry) {
        text += `<input id=\"${entry["id"]}\" type=\"button\" value=\"${entry["label"]}\"/>\n`;
    });
    contentElem.innerHTML = text;
    contents.forEach(function(entry) {
        document.querySelector(`#${entry["id"]}`).addEventListener('click', entry["func"])
    });
}
