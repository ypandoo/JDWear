import { Component } from '@angular/core';
import { NavController } from 'ionic-angular';
import { SetActivityPage } from '../set-activity/set-activity'
import { DeviceinfoPage } from '../deviceinfo/deviceinfo';
import { Platform } from 'ionic-angular';
import { ToastController } from 'ionic-angular';

declare var cordova: any;

@Component({
  selector: 'page-self',
  templateUrl: 'self.html'
})
export class SelfPage {

  constructor(public navCtrl: NavController, public platform: Platform, public toastCtrl: ToastController) {

  }

  more() {
    this.navCtrl.push(SetActivityPage);
  }

  deviceInfo(){
    this.navCtrl.push(DeviceinfoPage);
  }
}