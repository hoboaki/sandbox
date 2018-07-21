const $ = require('jquery');
const Grid = require('editable-grid');
const remote = require('electron').remote;
const Menu = remote.Menu;
const MenuItem = remote.MenuItem;

window.onload = function() {
    // MenuBarテスト（TitleBarの上でのみ反応）
    {        
        let menu = new Menu();
        menu.append(new MenuItem({ label: 'MenuItem1', click: function() { console.log('item 1 clicked'); } }));
        menu.append(new MenuItem({ type: 'separator' }));
        menu.append(new MenuItem({ label: 'MenuItem2', type: 'checkbox', checked: true }));
        
        document.getElementById('titleBar').addEventListener('contextmenu', function (e) {
            e.preventDefault();
            menu.popup(remote.getCurrentWindow());
        }, false);
    }

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

    // Grid高さ固定
    contents.push({id: "GridFixedHeight", label: "GridFixedHeight", func: onGridFixedHeightBtnClicked})
    function onGridFixedHeightBtnClicked() {
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

    // GridTree
    contents.push({id: "GridTree", label: "GridTree", func: onGridTreeBtnClicked})
    function onGridTreeBtnClicked() {
        let el = $('#content');

        var grid = new Grid({
            treeMode: true, // <- note
            childData: function (parentId/*, parentObj*/) {     // <- note
                // child data can also be loaded asynchronously
                // the return for this function must be a deferred object
                // the return in the deferred object must be an array
                if (parentId === 'id-3') {
                    return $.Deferred().resolve([
                        {
                            id: 'id-10',
                            a: 'a-3',
                            b: 'b-3',
                            c: 'c-3'
                        },
                        {
                            id: 'id-11',
                            a: 'a-3',
                            b: 'b-3',
                            c: 'c-3'
                        }
                    ]);
                }
                return $.Deferred().resolve([]);
            },
            el: el,
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
            data: [
                {
                    id: 'id-1',
                    a: 'a',
                    b: 'b',
                    c: 'c',
                    children: [
                        {
                            id: 'id-2',
                            a: 'a-1',
                            b: 'b-1',
                            c: 'c-1',
                            children: [
                                {
                                    id: 'id-3',
                                    a: 'a-2',
                                    b: 'b-2',
                                    c: 'c-2'
                                }
                            ]
                        }
                    ]
                },
                {
                    id: 'id-4',
                    a: 'a',
                    b: 'b',
                    c: 'c',
                    children: 'empty'
                }
            ]
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

