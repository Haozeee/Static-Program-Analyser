const fs = require('fs')
const util = require('util')
const axios = require('axios')
const parseString = require('xml2js').parseString
const { google } = require('googleapis')

const auth = new google.auth.GoogleAuth({
  keyFile: "keys.json",
  scopes: "https://www.googleapis.com/auth/spreadsheets",
})

const config = {
  method: 'post',
  maxBodyLength: Infinity,
  url: '',
  headers: {
    'Content-Type': 'text/plain'
  },
  data: ''
}

const spreadsheetId = process.argv[2]
const postURL = process.argv[3]
const commitSha = process.argv[4]
const testMode = process.argv[5]
const mainSheet = []
let hasFailure = false

// Simple NanoID Generator Simulation not always unqiue
function generateNanoId(length = 21) {
  const alphabet = '0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'
  let nanoid = ''

  for (let i = 0; i < length; i++) {
    nanoid += alphabet[Math.floor(Math.random() * alphabet.length)]
  }

  return nanoid
}

const createNewSheet = async (sheetID) => {

  const authClientObject = await auth.getClient()

  const googleSheetsInstance = google.sheets({ version: "v4", auth: authClientObject })

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
    }
    return await googleSheetsInstance.spreadsheets.batchUpdate(request)
  }

  return await addSheet()
}

const insertToGSheet = async (values, col, sheetName) => {

  const authClientObject = await auth.getClient()

  const googleSheetsInstance = google.sheets({ version: "v4", auth: authClientObject })

  let firstRow = "2"

  googleSheetsInstance.spreadsheets.values.append({
    auth, //auth object
    spreadsheetId, //spreadsheet id
    range: `${sheetName}!A${firstRow}:${col}`, //sheet name and range of cells
    valueInputOption: "RAW", // The information will be passed according to what the usere passes in as date, number or text
    resource: {
        values: values,
    },
  })
}

const extractData = async (xml) => {

  let array = []

  parseString(xml, (err, result) => {

    const queries = result.test_results.queries
    queries[0].query.map(query => {

      const x1 = `Query ${query.id[0]._}: ${query.id[0].$.comment}`
      const x2 = JSON.stringify(query.id[0].$).replace("{", "").replace("}", "")
      const x3 = query.querystr[0]
      const x4 = query.stuans[0]
      const x5 = query.correct[0]
      const x6 = query.time_taken[0]
      const x7 = query.passed ? "Passed" : "Failed"
      const x8 = " "

      array.push(x1)
      array.push(x2)
      array.push(x3)
      array.push(x4)
      array.push(x5)
      array.push(x6)
      array.push(x7)
      array.push(x8)

      if (x7 === "Failed") {
        hasFailure = true
      }
    })
  })

  return array
}

const resultDirPath = `${__dirname}/../results`

fs.readdir(resultDirPath, { withFileTypes: true }, async (err, resultDir) => {

  let col = "A"

  for (const element of resultDir) {
    try {
      const file = element
      const xmlData = fs.readFileSync(`${resultDirPath}/${file.name}`, 'utf-8')

      // Post to Remote Storage
      config.url = `${postURL}/${file.name}/${commitSha}`
      config.data = xmlData;

      axios(config)
        .then(function (response) {
          // console.log(JSON.stringify(response.data))
        })
        .catch(function (error) {
          // console.log(error)
        })

      const dataInArr = await extractData(xmlData)

      dataInArr.unshift(file.name)
      dataInArr.unshift(`${postURL}/common/${file.name}--${commitSha}`)
      dataInArr.unshift(" ")
      mainSheet.push(dataInArr)
      
      col = String.fromCharCode(col.charCodeAt(0) + 1)
    } catch (err) {
    }
  }

  if (testMode || hasFailure) {
    const output = mainSheet[0].map((_, colIndex) => mainSheet.map(row => row[colIndex]))
  
    const sheetName = generateNanoId(6)
    const sheet = await createNewSheet(sheetName)
    await insertToGSheet(output, col, sheetName)

    console.log(`url=https://docs.google.com/spreadsheets/d/${spreadsheetId}/preview#gid=${sheet.data.replies[0].addSheet.properties.sheetId}`)
  } else {
    console.log(`url="All passed"`)
  }
})