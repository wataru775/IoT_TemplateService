<?php

namespace App\Http\Controllers;

use App\Template;
use Illuminate\Http\Request;
use Illuminate\Support\Facades\Log;

class RestappController extends Controller
{
    /**
     * Display a listing of the resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function index()
    {
        $templates = Template::all();
        return response()->json($templates);
    }

    /**
     * Show the form for creating a new resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function create()
    {
        return response()->json(["code"=>"OK"]);
    }

    /**
     * Store a newly created resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @return \Illuminate\Http\Response
     */
    public function store(Request $request)
    {
        //
        Log::debug($request->all()['temperature']);
        $temp = new Template;
        $timestamp = now();
        $temp->datetime = $timestamp;
        $temp->sensor_id = $request->all()['terminal'];
        $temp->template = $request->all()['temperature'];
        $temp->humidity = $request->all()['humidity'];
        $temp->created_at = $timestamp;
        $temp->updated_at = $timestamp;

        $temp->save();


        return response()->json(["code"=>"OK"]);

    }

    /**
     * Display the specified resource.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function show($id)
    {
        //
        return response()->json(["code"=>"OK"]);
    }

    /**
     * Show the form for editing the specified resource.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function edit($id)
    {
        //
        return response()->json(["code"=>"OK"]);
    }

    /**
     * Update the specified resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function update(Request $request, $id)
    {
        //
        return response()->json(["code"=>"OK"]);
    }

    /**
     * Remove the specified resource from storage.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function destroy($id)
    {
        //
        return response()->json(["code"=>"OK"]);
    }
}
