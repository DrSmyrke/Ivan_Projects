//-----------------------------------------------------------------------------
var app = {
	debug: true,
	error: false,
	actionProcess: false,
	url: undefined,
	data: {
		mode: 0,
		lents: {},
	},
	modsAvailable: [
		'Радуга',
		'Разделенщина',
		'Один цвет',
		'Мигалка',
		'Огонь',
		'',
		'',
		'',
	],
};

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
window.onload = function(){
	printLocation();
	updateData();
	openPage( document.location.pathname );
};



//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
function sendForm( form, callback = undefined )
{
	var request = makeHttpObject();
	var formData = new FormData( form );
	request.open( form.method, form.action, true );
	request.send( formData );

	request.onreadystatechange = function(){
		if( request.readyState == 4 ){
			if( request.status == 200 ){
				if( app.debug ) console.log( 'sendForm >:', request.responseText );
				let dataObject = JSON.parse( ( request.responseText != '' ) ? request.responseText : '{}' );
				if( callback != undefined ) callback( dataObject );
			}
		}
	};
}

//-----------------------------------------------------------------------------
function openPage( url = '' )
{
	if( app.debug ) console.info( 'openPage >:', url, app.url );

	if( app.url == url ) return;

	let obj = getContentBox();
	if( obj == undefined ) return;

	let title			= '';

	switch( url ){
		case '/':
			// title = 'Control';
			buildControlUI();
		break;

		case '/settings':
			// title = 'Настройки';
			buildSettingsUI();
		break;
	}

	app.url = url;

	if( title != '' ){
		window.history.pushState( {param: 'Value'}, title, url );
		document.title = title;
	}

	let footers = document.getElementsByTagName( 'FOOTER' );
	for( let i = 0; i < footers.length; i++ ){
		let footer = footers[ i ];
		let buttons = footer.getElementsByClassName( 'button' );
		for( let ii = 0; ii < buttons.length; ii++ ){
			let obj = buttons[ ii ];
			if( obj.lang == undefined || obj.lang == null ) continue;
			if( obj.lang == url ){
				obj.classList.add( 'selected' );
			}else{
				obj.classList.remove( 'selected' );
			}
		}
	}
}

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
function printHexData( array = new Uint8Array() )
{
	let string = '[';

	for( let i = 0; i < array.length; i++ ){
		if( i > 0 ) string += ' ';

		let s = array[ i ].toString( 16 );
		string += array[ i ] < 0x10 ? '0' + s : s;
	}

	string += ']';

	return string;
}

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
function buildControlUI()
{
	let obj = getContentBox();
	if( obj == undefined ) return;

	let box = document.createElement( 'div' );
	box.classList = 'block';
	box.innerHTML = '';
	obj.appendChild( box );

	let modeString = document.createElement( 'div' );
	modeString.classList = 'string';
	modeString.innerHTML = '<text>Режим</text>';
	box.appendChild( modeString );
	let modeBox = document.createElement( 'select' );
	modeBox.name = 'mode';
	modeBox.value = app.data.mode;
		for( let num in app.modsAvailable ){
			if( app.modsAvailable[ num ] == '' ) continue;
			let option = document.createElement( 'option' );
			option.value = num;
			option.label = app.modsAvailable[ num ];
			modeBox.appendChild( option );
		}
	modeBox.onchange = function(){
		changeParam( this );
		app.data.mode = this.value;
		buildControlUI();
	};
	modeString.appendChild( modeBox );

	addAbout( obj );

	
	//Интерфейсы режимов
	
	if( app.data.mode == 1 ){
		let box1 = document.createElement( 'div' );
		box1.classList = 'string';
		box1.innerHTML = '<text>Зона 1 <i>(верх)</i></text><input type="color" name="zone1up" value="#123456">';
		box.appendChild( box1 );
		let box2 = document.createElement( 'div' );
		box2.classList = 'string';
		box2.innerHTML = '<text>Зона 1 <i>(низ)</i></text><input type="color" name="zone1down" value="#123456">';
		box.appendChild( box2 );
	}
}

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
function buildSettingsUI()
{
	let obj = getContentBox();
	if( obj == undefined ) return;

	let box = document.createElement( 'div' );
	box.classList = 'block';
	box.innerHTML = '';
	obj.appendChild( box );

	// var request = makeHttpObject();
	// request.open( 'GET', '/get', true );
	// request.send( null );

	// request.onreadystatechange = function(){
	// 	if( request.readyState == 4 ){
	// 		if( request.status == 200 ){
	// 			if( app.debug ) console.log( 'buildSettingsUI >:', request.responseText );
	// 			let dataObject = JSON.parse( ( request.responseText != '' ) ? request.responseText : '{}' );

	// 			if( dataObject.hasOwnProperty( 'lents' ) ){
					for( let port in app.data.lents ){
						let data = app.data.lents[ port ];
						if( !data.hasOwnProperty( 'use' ) ) continue;
						if( !data.hasOwnProperty( 'leds' ) ) continue;

						let checked = ( Number( data.use ) ) ? ' checked' : '';

						let string = document.createElement( 'div' );
						string.classList = 'string';
						string.innerHTML = '<text>Port ' + port + '</text><text><input type="checkbox" name="port' + port + 'use" onchange="changeParam( this );"' + checked + '></text>';
						box.appendChild( string );
						let string2 = document.createElement( 'div' );
						string2.classList = 'string';
						string2.innerHTML = '<text>Lenta ' + port + ' count</text><text><input type="number" min="0" max="999" name="lenta' + port + 'leds" onchange="changeParam( this );" value="' + data.leds + '" size="3"></text>';
						box.appendChild( string2 );
					}
				// }

// 				if( dataObject.hasOwnProperty( 'lora_tx_power' ) ){
// 					setFieldValue( 'lora_tx_power', dataObject.lora_tx_power );
// 				}
// 				if( dataObject.hasOwnProperty( 'lora_lna' ) ){
// 					setFieldValue( 'lora_lna', dataObject.lora_lna );
// 				}
// 				if( dataObject.hasOwnProperty( 'lora_spf' ) ){
// 					setFieldValue( 'lora_spf', dataObject.lora_spf );
// 				}
// 				if( dataObject.hasOwnProperty( 'lora_bw' ) ){
// 					setFieldValue( 'lora_bw', dataObject.lora_bw );
// 				}
// 				if( dataObject.hasOwnProperty( 'channel' ) ){
// 					setFieldValue( 'channel', dataObject.channel );
// 				}
	// 		}
	// 	}
	// };

	addAbout( obj );
}

//-----------------------------------------------------------------------------
function setFieldValue( name = '', value = undefined )
{
	if( app.debug ) console.log( "setFieldValue >:", name, value );

	if( name == '' ) return;
	if( value == undefined ) return;

	let find = false;

	let fields = document.getElementsByTagName( 'input' );
	for( let i = 0; i < fields.length; i++ ){
		if( fields[ i ].name == name ){
			fields[ i ].value = value;
			find = true;
			break;
		}
	}

	if( find ) return;

	let selects = document.getElementsByTagName( 'select' );
	for( let i = 0; i < selects.length; i++ ){
		if( selects[ i ].name == name ){
			selects[ i ].value = value;
			find = true;
			break;
		}
	}

	if( find ) return;

	let divs = document.getElementsByTagName( 'div' );
	for( let i = 0; i < divs.length; i++ ){
		let div = divs[ i ];
		if( div.lang == name ){
			if( div.lastElementChild.classList.contains( 'value' ) ){
				if( value.length != undefined ){
					if( value.length == 2 && value[ 0 ] == 'value' ){
						div.lastElementChild.className = 'value';
						div.lastElementChild.innerText = value[ 1 ];
					}else{
						div.lastElementChild.className = '';
						for( let num in value ) div.lastElementChild.classList.add( value[ num ] );
					}
				}
				find = true;
				break;
			}
		}
	}
}

//-----------------------------------------------------------------------------
function changeParam( element )
{
	if( app.debug ) console.log( 'changeParam >:', element.name, element.value );

	let str = '';
	let value = undefined;

	if( element.type == 'checkbox' ){
		value = ( element.checked ) ? 1 : 0;
	}else{
		value = element.value;
	}

	str = 'param=' + element.name + '&value=' + value;

	if( value == undefined ) return;
	if( app.changeParam == element.name ) return;
	app.changeParam = element.name;

	var request = makeHttpObject();
	request.open( 'POST', '/set', true );
	request.setRequestHeader( 'Content-type','application/x-www-form-urlencoded' );
	request.send( str );

	request.onreadystatechange = function(){
		if( request.readyState == 4 ){
			app.changeParam = "";
			if( request.status == 200 ){
				if( app.debug ) console.log( 'changeParam >:', request.responseText );
				let dataObject = JSON.parse( ( request.responseText != '' ) ? request.responseText : '{}' );

				if( dataObject.hasOwnProperty( 'success' ) ){
					alert( dataObject.success );
				}
			}
		}
	};
}

//-----------------------------------------------------------------------------
function CheckBit( reg, bit ) 
{
	reg = Number( Number( reg ).toFixed() );
	bit = Number( Number( bit ).toFixed() );
	return ( ( reg & (1<<bit ) ) != 0 ) ? 1 : 0;
}

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
function updateData( callback = undefined )
{
	var request = makeHttpObject();
	request.open( 'GET', '/get', true );
	request.send( null );

	request.onreadystatechange = function(){
		if( request.readyState == 4 ){
			if( request.status == 200 ){
				if( app.debug ) console.log( 'updateData >:', request.responseText );
				let dataObject = JSON.parse( ( request.responseText != '' ) ? request.responseText : '{}' );

				if( dataObject.hasOwnProperty( 'mode' ) ) app.data.mode = dataObject.mode;
				if( dataObject.hasOwnProperty( 'lents' ) ) app.data.lents = dataObject.lents;

				if( callback != undefined ) callback();


				// setTimeout( updateData, 5000 );
			}else{
				app.error = true;
				if( callback != undefined ) callback();
			}
		}else{
			app.error = true;
			if( callback != undefined ) callback();
		}
	};
}

//-----------------------------------------------------------------------------
function addAbout( obj = undefined )
{
	if( obj == undefined ) return;

	let aboutBox = document.createElement( 'div' );
	aboutBox.innerHTML = 'Created by <a href="http://drsmyrke.ru" target="_blank">Dr.Smyrke</a>';
	obj.appendChild( aboutBox );
}

//-----------------------------------------------------------------------------
