<?php
namespace HttpService;

/**
 * Autogenerated by Thrift Compiler (0.10.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
use Thrift\Base\TBase;
use Thrift\Type\TType;
use Thrift\Type\TMessageType;
use Thrift\Exception\TException;
use Thrift\Exception\TProtocolException;
use Thrift\Protocol\TProtocol;
use Thrift\Protocol\TBinaryProtocolAccelerated;
use Thrift\Exception\TApplicationException;


final class UserOperation {
  const REGISTER = 1;
  const LOGIN = 2;
  const LOGOUT = 3;
  const MODIFY = 4;
  static public $__names = array(
    1 => 'REGISTER',
    2 => 'LOGIN',
    3 => 'LOGOUT',
    4 => 'MODIFY',
  );
}

class User {
  static $_TSPEC;

  /**
   * @var int
   */
  public $id = null;
  /**
   * @var string
   */
  public $name = null;
  /**
   * @var string
   */
  public $phoneNumber = null;
  /**
   * @var string
   */
  public $email = null;
  /**
   * @var string
   */
  public $password = null;

  public function __construct($vals=null) {
    if (!isset(self::$_TSPEC)) {
      self::$_TSPEC = array(
        1 => array(
          'var' => 'id',
          'type' => TType::I64,
          ),
        2 => array(
          'var' => 'name',
          'type' => TType::STRING,
          ),
        3 => array(
          'var' => 'phoneNumber',
          'type' => TType::STRING,
          ),
        4 => array(
          'var' => 'email',
          'type' => TType::STRING,
          ),
        5 => array(
          'var' => 'password',
          'type' => TType::STRING,
          ),
        );
    }
    if (is_array($vals)) {
      if (isset($vals['id'])) {
        $this->id = $vals['id'];
      }
      if (isset($vals['name'])) {
        $this->name = $vals['name'];
      }
      if (isset($vals['phoneNumber'])) {
        $this->phoneNumber = $vals['phoneNumber'];
      }
      if (isset($vals['email'])) {
        $this->email = $vals['email'];
      }
      if (isset($vals['password'])) {
        $this->password = $vals['password'];
      }
    }
  }

  public function getName() {
    return 'User';
  }

  public function read($input)
  {
    $xfer = 0;
    $fname = null;
    $ftype = 0;
    $fid = 0;
    $xfer += $input->readStructBegin($fname);
    while (true)
    {
      $xfer += $input->readFieldBegin($fname, $ftype, $fid);
      if ($ftype == TType::STOP) {
        break;
      }
      switch ($fid)
      {
        case 1:
          if ($ftype == TType::I64) {
            $xfer += $input->readI64($this->id);
          } else {
            $xfer += $input->skip($ftype);
          }
          break;
        case 2:
          if ($ftype == TType::STRING) {
            $xfer += $input->readString($this->name);
          } else {
            $xfer += $input->skip($ftype);
          }
          break;
        case 3:
          if ($ftype == TType::STRING) {
            $xfer += $input->readString($this->phoneNumber);
          } else {
            $xfer += $input->skip($ftype);
          }
          break;
        case 4:
          if ($ftype == TType::STRING) {
            $xfer += $input->readString($this->email);
          } else {
            $xfer += $input->skip($ftype);
          }
          break;
        case 5:
          if ($ftype == TType::STRING) {
            $xfer += $input->readString($this->password);
          } else {
            $xfer += $input->skip($ftype);
          }
          break;
        default:
          $xfer += $input->skip($ftype);
          break;
      }
      $xfer += $input->readFieldEnd();
    }
    $xfer += $input->readStructEnd();
    return $xfer;
  }

  public function write($output) {
    $xfer = 0;
    $xfer += $output->writeStructBegin('User');
    if ($this->id !== null) {
      $xfer += $output->writeFieldBegin('id', TType::I64, 1);
      $xfer += $output->writeI64($this->id);
      $xfer += $output->writeFieldEnd();
    }
    if ($this->name !== null) {
      $xfer += $output->writeFieldBegin('name', TType::STRING, 2);
      $xfer += $output->writeString($this->name);
      $xfer += $output->writeFieldEnd();
    }
    if ($this->phoneNumber !== null) {
      $xfer += $output->writeFieldBegin('phoneNumber', TType::STRING, 3);
      $xfer += $output->writeString($this->phoneNumber);
      $xfer += $output->writeFieldEnd();
    }
    if ($this->email !== null) {
      $xfer += $output->writeFieldBegin('email', TType::STRING, 4);
      $xfer += $output->writeString($this->email);
      $xfer += $output->writeFieldEnd();
    }
    if ($this->password !== null) {
      $xfer += $output->writeFieldBegin('password', TType::STRING, 5);
      $xfer += $output->writeString($this->password);
      $xfer += $output->writeFieldEnd();
    }
    $xfer += $output->writeFieldStop();
    $xfer += $output->writeStructEnd();
    return $xfer;
  }

}

class Log {
  static $_TSPEC;

  /**
   * @var int
   */
  public $id = null;
  /**
   * @var int
   */
  public $usr_id = null;
  /**
   * @var int
   */
  public $op = null;

  public function __construct($vals=null) {
    if (!isset(self::$_TSPEC)) {
      self::$_TSPEC = array(
        1 => array(
          'var' => 'id',
          'type' => TType::I32,
          ),
        2 => array(
          'var' => 'usr_id',
          'type' => TType::I64,
          ),
        3 => array(
          'var' => 'op',
          'type' => TType::I32,
          ),
        );
    }
    if (is_array($vals)) {
      if (isset($vals['id'])) {
        $this->id = $vals['id'];
      }
      if (isset($vals['usr_id'])) {
        $this->usr_id = $vals['usr_id'];
      }
      if (isset($vals['op'])) {
        $this->op = $vals['op'];
      }
    }
  }

  public function getName() {
    return 'Log';
  }

  public function read($input)
  {
    $xfer = 0;
    $fname = null;
    $ftype = 0;
    $fid = 0;
    $xfer += $input->readStructBegin($fname);
    while (true)
    {
      $xfer += $input->readFieldBegin($fname, $ftype, $fid);
      if ($ftype == TType::STOP) {
        break;
      }
      switch ($fid)
      {
        case 1:
          if ($ftype == TType::I32) {
            $xfer += $input->readI32($this->id);
          } else {
            $xfer += $input->skip($ftype);
          }
          break;
        case 2:
          if ($ftype == TType::I64) {
            $xfer += $input->readI64($this->usr_id);
          } else {
            $xfer += $input->skip($ftype);
          }
          break;
        case 3:
          if ($ftype == TType::I32) {
            $xfer += $input->readI32($this->op);
          } else {
            $xfer += $input->skip($ftype);
          }
          break;
        default:
          $xfer += $input->skip($ftype);
          break;
      }
      $xfer += $input->readFieldEnd();
    }
    $xfer += $input->readStructEnd();
    return $xfer;
  }

  public function write($output) {
    $xfer = 0;
    $xfer += $output->writeStructBegin('Log');
    if ($this->id !== null) {
      $xfer += $output->writeFieldBegin('id', TType::I32, 1);
      $xfer += $output->writeI32($this->id);
      $xfer += $output->writeFieldEnd();
    }
    if ($this->usr_id !== null) {
      $xfer += $output->writeFieldBegin('usr_id', TType::I64, 2);
      $xfer += $output->writeI64($this->usr_id);
      $xfer += $output->writeFieldEnd();
    }
    if ($this->op !== null) {
      $xfer += $output->writeFieldBegin('op', TType::I32, 3);
      $xfer += $output->writeI32($this->op);
      $xfer += $output->writeFieldEnd();
    }
    $xfer += $output->writeFieldStop();
    $xfer += $output->writeStructEnd();
    return $xfer;
  }

}

class AuthException extends TException {
  static $_TSPEC;

  /**
   * @var int
   */
  public $errorCode = null;
  /**
   * @var string
   */
  public $errorInfo = null;

  public function __construct($vals=null) {
    if (!isset(self::$_TSPEC)) {
      self::$_TSPEC = array(
        1 => array(
          'var' => 'errorCode',
          'type' => TType::I32,
          ),
        2 => array(
          'var' => 'errorInfo',
          'type' => TType::STRING,
          ),
        );
    }
    if (is_array($vals)) {
      if (isset($vals['errorCode'])) {
        $this->errorCode = $vals['errorCode'];
      }
      if (isset($vals['errorInfo'])) {
        $this->errorInfo = $vals['errorInfo'];
      }
    }
  }

  public function getName() {
    return 'AuthException';
  }

  public function read($input)
  {
    $xfer = 0;
    $fname = null;
    $ftype = 0;
    $fid = 0;
    $xfer += $input->readStructBegin($fname);
    while (true)
    {
      $xfer += $input->readFieldBegin($fname, $ftype, $fid);
      if ($ftype == TType::STOP) {
        break;
      }
      switch ($fid)
      {
        case 1:
          if ($ftype == TType::I32) {
            $xfer += $input->readI32($this->errorCode);
          } else {
            $xfer += $input->skip($ftype);
          }
          break;
        case 2:
          if ($ftype == TType::STRING) {
            $xfer += $input->readString($this->errorInfo);
          } else {
            $xfer += $input->skip($ftype);
          }
          break;
        default:
          $xfer += $input->skip($ftype);
          break;
      }
      $xfer += $input->readFieldEnd();
    }
    $xfer += $input->readStructEnd();
    return $xfer;
  }

  public function write($output) {
    $xfer = 0;
    $xfer += $output->writeStructBegin('AuthException');
    if ($this->errorCode !== null) {
      $xfer += $output->writeFieldBegin('errorCode', TType::I32, 1);
      $xfer += $output->writeI32($this->errorCode);
      $xfer += $output->writeFieldEnd();
    }
    if ($this->errorInfo !== null) {
      $xfer += $output->writeFieldBegin('errorInfo', TType::STRING, 2);
      $xfer += $output->writeString($this->errorInfo);
      $xfer += $output->writeFieldEnd();
    }
    $xfer += $output->writeFieldStop();
    $xfer += $output->writeStructEnd();
    return $xfer;
  }

}


