<?php

final class ActionType
{
    const START = 1;
    const STOP = 2;
}

class Log
{
    public $functionName;
    public $actionType;
    public $time;

    public function __construct($functionName, $actionType)
    {
        $this->functionName = $functionName;
        $this->actionType = $actionType;
        $this->time = time();
    }
}


class Logger
{
    private $logs = array();
    private $logStack = array();
    private $runtime = array();


    public function log($functionName, $actionType)
    {
        $this->logs[] = new Log($functionName, $actionType);
    }

    public function analysisTime()
    {
        foreach ($this->logs as $log) {
            $stackLog = end($this->logStack);
        }
    }
}
