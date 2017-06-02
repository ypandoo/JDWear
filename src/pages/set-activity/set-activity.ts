import { Component } from '@angular/core';
import { IonicPage, NavController, NavParams } from 'ionic-angular';
import { LanguageSetActivityPage } from '../language-set-activity/language-set-activity';
import { TranslateService } from '@ngx-translate/core';

/**
 * Generated class for the SetActivityPage page.
 *
 * See http://ionicframework.com/docs/components/#navigation for more info
 * on Ionic pages and navigation.
 */
@IonicPage()
@Component({
  selector: 'page-set-activity',
  templateUrl: 'set-activity.html',
})


export class SetActivityPage {
  items = [
    'LanguageSetActivity_Title',
    'HelpSetActivity_Title',
    'Home_Target',
    'ChangePassward'
  ];

  itemSelected(item: string) {
    switch(item)
    {
      case 'LanguageSetActivity_Title':
      this.navCtrl.push(LanguageSetActivityPage);
      break;

      default:
      console.log('click'+item);
    }
  }

  onSelectLanguage(selectedValue: any) {

    this.translate.use(selectedValue);
    console.log('Language Selected', selectedValue);
  }

  constructor(public navCtrl: NavController, public navParams: NavParams, private translate: TranslateService) {
  }

  ionViewDidLoad() {
    console.log('ionViewDidLoad SetActivityPage');
  }

}
