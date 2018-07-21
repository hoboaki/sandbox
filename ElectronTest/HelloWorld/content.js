const $ = require('jquery');
const Grid = require('editable-grid');

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
    // Gridテスト
    contents.push({id: "GridTest", label: "GridTest", func: onGridTestBtnClicked})
    function onGridTestBtnClicked() {
        let el = $('#content');

        var fixedHeight = $('<div style="height: 300px"></div>');
        el.append(fixedHeight);

        var data = [];
        for (var i = 0  ; i < 20; i++) {
            data.push({
                id: 'id-' + i,
                a: 'a',
                b: 'b',
                c: 'c'
            });
        }

        var grid = new Grid({
            el: fixedHeight,
            columns: [
                {
                    id: 'a',
                    title: 'a',
                    width: '33.3%'
                },
                {
                    id: 'b',
                    title: 'b',
                    width: '33.3%'
                },
                {
                    id: 'c',
                    title: 'c',
                    width: '33.3%'
                }
            ],
            data: data
        });
        grid.render();
    }

    // コンテンツ展開
    const menuElem = document.getElementById('menu');
    let text = "";
    contents.forEach(function(entry) {
        text += `<input id=\"${entry["id"]}\" type=\"button\" value=\"${entry["label"]}\"/>\n`;
    });
    menuElem.innerHTML = text;
    contents.forEach(function(entry) {
        document.querySelector(`#${entry["id"]}`).addEventListener('click', entry["func"])
    });
}

