import { Component, ChangeDetectorRef } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { FormsModule } from '@angular/forms';
import { CommonModule } from '@angular/common';

@Component({
  selector: 'app-root',
  standalone: true,
  imports: [FormsModule, CommonModule],
  templateUrl: './app.html',
  styleUrl: './app.css'
})
export class App {
  city: string = '';
  weather: any = null;
  error: string = '';
  loading: boolean = false;

  private apiKey = 'a57dde44b118f19177b4cd5f17af4dbe';

  constructor(private http: HttpClient, private cd: ChangeDetectorRef) {}

  getWeather() {
    if (!this.city) return;
    
    this.loading = true;
    this.error = '';
    this.weather = null;

    const url = `https://api.openweathermap.org/data/2.5/weather?q=${this.city}&appid=${this.apiKey}&units=metric`;

    this.http.get(url).subscribe({
      next: (data) => {
        this.weather = data;
        this.loading = false;
        this.cd.detectChanges(); // force Angular to update the view
      },
      error: (err) => {
        this.error = 'City not found — please try again';
        this.loading = false;
        this.cd.detectChanges();
      }
    });
  }
}