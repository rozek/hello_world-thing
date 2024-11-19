import Thing from "../../../src/lib/thing"

export default class hello_world extends Thing {
  constructor (...ArgList:any[]) {
    super(...ArgList)
  }

  async setRGB (R:number, G:number, B:number):Promise<void> {
    const Datagram = new Uint8Array([
      255 * Math.max(0,Math.min(R,1)),
      255 * Math.max(0,Math.min(G,1)),
      255 * Math.max(0,Math.min(B,1)),
    ])
    await this.send('setRGB',Datagram)
  }

/**** API Documentation ****/

  public api = [{
    name:  'setRGB',
    args:  [
      'R: 0 to 1',
      'G: 0 to 1',
      'B: 0 to 1'
    ]
  }]
}