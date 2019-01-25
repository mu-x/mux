'use strict'

const path = require('path')

const assert =require('assert')
const puppeteer = require('puppeteer')

const Server = require('../server/server.js')
const {temporaryDirectory} = require('../server/utils.js')

describe('Browser', () => {
  var direcotry, server, url, browser, page

  beforeEach(async () => {
    direcotry = await temporaryDirectory(path.join(__dirname, 'data'))
    server = new Server({port: 0, root: direcotry})
    url = `http://localhost:${server.listener.address().port}`
    browser = await puppeteer.launch(process.env.DEBUG ? {headless: false, slowMo: 200} : {})
    page = await browser.newPage()
  })

  afterEach(async () => { 
    await server.stop()
    if (!process.env.DEBUG)
      await browser.close()
  })

  const clickItem = async (id, expectedPath = '') => {
    await page.evaluate((id) => document.getElementById(id).click(), id)
    await page.waitFor(10)
    if (expectedPath)
      assert(page.url(), url + expectedPath)
  }

  const expectDirectroryItems = async (expected) => {
    const content = await page.evaluate(() => $('#directory').find('.item').toArray().map(i => i.id))
    assert.deepEqual(content, expected)
  }

  it('Navigation', async () => {
    await page.goto(url)
    await expectDirectroryItems([
      'Directory with spaces', 'empty', 'images', 'previews', 
      'Vary+ strange& directory=', 'text.txt'])

    await clickItem('Directory with spaces', '/Directory with spaces')
    await expectDirectroryItems(['hello world.txt'])

    /* TODO:
      await clickItem('hello world.txt')
      const download = browser.pages[browser.pages.length - 1]
      assert(download.url(), url + '/api/content/hello world.txt')
    */

    await clickItem('path0', '/')
    await expectDirectroryItems([
      'Directory with spaces', 'empty', 'images', 'previews', 
      'Vary+ strange& directory=', 'text.txt'])

    await clickItem('Vary+ strange& directory=')
    await expectDirectroryItems(['another file', 'Is file&', 'part&of=url'])
  })
})