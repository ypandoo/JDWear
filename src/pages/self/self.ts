import { Component } from '@angular/core';
import { NavController } from 'ionic-angular';
import { SetActivityPage } from '../set-activity/set-activity'
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

  pushPage() {
    //this.navCtrl.push(SetActivityPage);
    this.platform.ready().then(() => {
      cordova.plugins.jdwear.coolMethod(
        "======> WORK"
        ,(e)=>{
          let toast = this.toastCtrl.create({
                        message: e,
                        duration: 3000
                      });
          toast.present();
        }
        ,(e)=>{console.log(e)}
        );
    });
  }
}