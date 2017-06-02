import { Component } from '@angular/core';
import { NavController } from 'ionic-angular';
import { SetActivityPage } from '../set-activity/set-activity'

@Component({
  selector: 'page-self',
  templateUrl: 'self.html'
})
export class SelfPage {

  constructor(public navCtrl: NavController) {

  }

  pushPage(){
    this.navCtrl.push(SetActivityPage);
  }

  

}
