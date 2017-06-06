import { Component } from '@angular/core';
import { IonicPage, NavController, NavParams } from 'ionic-angular';
import { Platform } from 'ionic-angular';
import { ToastController } from 'ionic-angular';
declare var cordova: any;

/**
 * Generated class for the DeviceinfoPage page.
 *
 * See http://ionicframework.com/docs/components/#navigation for more info
 * on Ionic pages and navigation.
 */
@IonicPage()
@Component({
  selector: 'page-deviceinfo',
  templateUrl: 'deviceinfo.html',
})
export class DeviceinfoPage {

  constructor(public navCtrl: NavController, public navParams: NavParams,public platform: Platform, public toastCtrl: ToastController) {
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

  ionViewDidLoad() {
    console.log('ionViewDidLoad DeviceinfoPage');
  }

}
