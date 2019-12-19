var MongoClient = require('mongodb').MongoClient;
var database_pass = require('./database_pass');

function connectDB(callback) {
	var url = database_pass.url;
	MongoClient.connect(url, function(err, db) {
		if(err) {
			console.log(err);
			callback(err, null);
			return;
		}
		console.log("db1",'connected');
		callback(err, db);
	});
}

var payment;
var collectionName;
var collection;

exports.insert_payments = function(collections, collection_name, json, callback) {
	collectionName = collection_name;
	collection = collections
	connectDB(function (err, db) {
		console.log(collections);
		var dbo = db.db(collections);
				//from members collections
		dbo.collection("members").find({"first_name": json.first_name, "second_name": json.second_name}).toArray(function (err, result) {
			if (err) {
				callback(err, null);
				db.close();
				return;
			}
			console.log("db2", result);
			if(result.length == 0){
				callback(null, "-1");//not exist
				db.close();
				return;
			}else{
				payment = {
					memberId: result[0]._id,
					weeks_remaining: json.weeks_remaining,
					amount: json.amount
				};
				db.close();


				insert(function (err, res) {
					if (err) {
						callback(err, null);
						return;
					}
					console.log(res);
					callback(null ,res);
					return;
				});
			}
		});
	});
}

function insert(callback) {

	connectDB(function (err, db){
		var dbo = db.db(collection);
		dbo.collection(collectionName).insertOne(payment, function (err, res) {
			if (err) {
				db.close();
				console.log("db3");
				callback(err, null);
			}
			console.log("db4", "successful");

			db.close();
			callback(err, "1");
		});
	});
}