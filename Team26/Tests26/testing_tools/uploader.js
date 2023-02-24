const fs = require('fs');
const util = require('util');
const parseString = require('xml2js').parseString;
const { google } = require('googleapis');

const auth = new google.auth.GoogleAuth({
  keyFile: "keys.json",
  scopes: "https://www.googleapis.com/auth/spreadsheets",
});

const spreadsheetId = process.argv[2];


// Simple NanoID Generator Simulation not always unqiue
function generateNanoId(length = 21) {
  const alphabet = '0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz';
  let nanoid = '';

  for (let i = 0; i < length; i++) {
    nanoid += alphabet[Math.floor(Math.random() * alphabet.length)];
  }

  return nanoid;
}

const createNewSheet = async (sheetID) => {

  const authClientObject = await auth.getClient();

  const googleSheetsInstance = google.sheets({ version: "v4", auth: authClientObject });

  const addSheet = async () => {
    const request = {
      spreadsheetId: spreadsheetId,
      resource: {
        requests: [{
          addSheet: {
            properties: {
              title: sheetID
            }
          }
        }]
      },
      auth: auth
    };
    return await googleSheetsInstance.spreadsheets.batchUpdate(request);
  }

  return await addSheet();
}

const insertToGSheet = async (values, col, sheetName) => {

  const authClientObject = await auth.getClient();

  const googleSheetsInstance = google.sheets({ version: "v4", auth: authClientObject });

  let firstRow = "2"

  googleSheetsInstance.spreadsheets.values.append({
    auth, //auth object
    spreadsheetId, //spreadsheet id
    range: `${sheetName}!${col}${firstRow}:${col}`, //sheet name and range of cells
    valueInputOption: "RAW", // The information will be passed according to what the usere passes in as date, number or text
    resource: {
        values: values.map((value) => [value]),
    },
  });
}

const extractData = async (xml) => {

  let array = []

  parseString(xml, (err, result) => {

    const queries = result.test_results.queries;
    queries[0].query.map(query => {

      // console.log(util.inspect(query, { depth: null }))

      const x1 = `Query ${query.id[0]._}: ${query.id[0].$.comment}`
      const x2 = JSON.stringify(query.id[0].$).replace("{", "").replace("}", "")
      const x3 = query.querystr[0]
      const x4 = query.stuans[0]
      const x5 = query.correct[0]
      const x6 = query.time_taken[0]
      const x7 = query.passed ? "Passed" : "Failed"
      const x8 = " "

      array.push(x1);
      array.push(x2);
      array.push(x3);
      array.push(x4);
      array.push(x5);
      array.push(x6);
      array.push(x7);
      array.push(x8);

    })
  });

  return array;
}

const resultDirPath = `${__dirname}/../results`;

fs.readdir(resultDirPath, { withFileTypes: true }, async (err, resultDir) => {

  let col = "A";

  const sheetName = generateNanoId(6)
  const sheet = await createNewSheet(sheetName)
  // console.log(util.inspect(sheet, { depth: null }))
  console.log(`https://docs.google.com/spreadsheets/d/${spreadsheetId}/preview#gid=${sheet.data.replies[0].addSheet.properties.sheetId}`)

  for (let i = 0; i < resultDir.length; i++) {
    try {
      const file = resultDir[i];
      // console.log(`${resultDirPath}/${file.name}`)
      xmlData = fs.readFileSync(`${resultDirPath}/${file.name}`, 'utf-8')
      const dataInArr = await extractData(xmlData)
  
      dataInArr.unshift(file.name)
      dataInArr.unshift(" ")
      
      const gSheetInstance = await insertToGSheet(dataInArr, col, sheetName)
      // console.log(gSheetInstance)
      col = String.fromCharCode(col.charCodeAt(0) + 1)
    } catch (err) {

    }
  }
})